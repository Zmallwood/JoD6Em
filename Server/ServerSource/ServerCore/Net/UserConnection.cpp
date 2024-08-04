/*
 * UserConnection.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "UserConnection.hpp"
#include "ServerCore/Net/WebSocketServer.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"
#include "MessageCodes.hpp"
#include "NetConfiguration.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/UserGameInstance/Cursor/Cursor.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace JoD {
    UserConnection::UserConnection(tcp::socket socket)
        : m_user_game_instance_engine(std::make_shared<UserGameInstanceEngine>(*this)),
        m_player(std::make_shared<Player>()),
        m_cursor(std::make_shared<Cursor>(*this)){
        std::thread(
            &UserConnection::DoSession, this,
            std::move(socket)).detach();
    }
    
    void UserConnection::DoSession(tcp::socket socket) {
        try{
            // Construct the stream by moving in the socket.
            websocket::stream<tcp::socket> ws{std::move(socket)};
            // Set a decorator to change the Server of the handshake.
            ws.set_option(
                websocket::stream_base::decorator(
                    [](websocket::response_type &res){
                        res.set(
                            http::field::server,
                            std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-server-sync");
                    }));
            ws.accept(); // Accept the websocket handshake.
            ws.text(false); // Receive binary data, not text.
            while (true){
                m_user_game_instance_engine->Update();
                m_user_game_instance_engine->Render(ws);
                while (true){
                    beast::flat_buffer buffer; // This buffer will hold the incoming message.
                    ws.read(buffer); // Read a message.
                    const auto message = buffer_cast<int *>(buffer.data());
                    if (*message == MessageCodes::k_canvas_size){
                        auto w = (int)message[1];
                        auto h = (int)message[2];
                        m_canvas_size = {w, h};
                    }else if (*message == MessageCodes::k_left_mouse_down) {
                        m_user_game_instance_engine->m_mouse_input->
                        RegisterMouseDown(
                            MouseButtons::left);
                    }else if (*message == MessageCodes::k_right_mouse_down) {
                        m_user_game_instance_engine->m_mouse_input->
                        RegisterMouseDown(
                            MouseButtons::right);
                    }else if (*message == MessageCodes::k_mouse_position) {
                        auto x = message[1] / net_constants::k_float_precision;
                        auto y = message[2] / net_constants::k_float_precision;
                        m_mouse_position = {x, y};
                    }else if (*message == MessageCodes::k_frame_finished) {
                        break;
                    }
                }
            }
        }
        catch (beast::system_error const &se){
            // This indicates that the session was closed.
            if (se.code() != websocket::error::closed)
                std::cerr << "Error: " << se.code().message() << std::endl;
        }
        catch (std::exception const &e){
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    void UserConnection::SendImageDrawInstruction(WebSocket &ws,
                                                      std::string_view
                                                      image_name,
                                                      RectF destination){
        SendImageDrawInstruction(ws, Hash(image_name), destination);
    }
    
    void UserConnection::SendImageDrawInstruction(WebSocket &ws,
                                                      int image_name_hash,
                                                      RectF destination){
        auto msg_code = MessageCodes::k_draw_image_instr;
        auto x = (int)(destination.x * net_constants::k_float_precision);
        auto y = (int)(destination.y * net_constants::k_float_precision);
        auto w = (int)(destination.w * net_constants::k_float_precision);
        auto h = (int)(destination.h * net_constants::k_float_precision);
        auto data = std::vector<int>();
        data.push_back(msg_code);
        data.push_back(image_name_hash);
        data.push_back(x);
        data.push_back(y);
        data.push_back(w);
        data.push_back(h);
        ws.write(boost::asio::buffer(data));
    }
    
    void UserConnection::SendTextDrawInstruction(WebSocket &ws,
                                                     std::string_view text,
                                                     PointF position) {
        auto msg_code = MessageCodes::k_draw_string_instr;
        auto x = (int)(position.x * net_constants::k_float_precision);
        auto y = (int)(position.y * net_constants::k_float_precision);
        auto data = std::vector<int>();
        data.push_back(msg_code);
        data.push_back(x);
        data.push_back(y);
        data.push_back(text.length());
        for (auto c : text) {
            data.push_back((int)c);
        }
        
        ws.write(boost::asio::buffer(data));
    }
    
    void UserConnection::SendPresentCanvasInstruction(WebSocket &ws){
        auto msg_code_present = MessageCodes::k_apply_buffer;
        ws.write(
            boost::asio::buffer(&msg_code_present,sizeof(msg_code_present)));
    }
    
    float UserConnection::GetAspectRatio() {
        return static_cast<float>(m_canvas_size.w) / m_canvas_size.h;
    }
}