/*
 * UserConnection.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "UserConnection.h"
#include "ServerCore/Net/WebSocketServer.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.h"
#include "ServerCore/UserGameInstance/ServerEngine.h"
#include "MessageCodes.h"
#include "NetConfiguration.h"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.h"
#include "ServerCore/UserGameInstance/Cursor/Cursor.h"
#include "Theme0/Scenes/Main/Process/TileHovering.h"
#include "Theme0/Scenes/Main/Process/MouseMovement.h"
#include "Theme0/Scenes/Main/Process/MobTargeting.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace jod {
    user_connection::user_connection(tcp::socket socket)
        : m_server_engine(std::make_shared<server_engine>(*this)),
        m_player(std::make_shared<player>()),
        m_tile_hovering(std::make_shared<tile_hovering>(*this)),
        m_mouse_movement(std::make_shared<mouse_movement>(*this)),
        m_cursor(std::make_shared<cursor>(*this)),
        m_mob_targeting(std::make_shared<mob_targeting>(*this)){
        std::thread(
            &user_connection::do_session, this,
            std::move(socket)).detach();
    }
    
    void user_connection::do_session(tcp::socket socket) {
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
                m_server_engine->update();
                m_server_engine->render(ws);
                while (true){
                    beast::flat_buffer buffer; // This buffer will hold the incoming message.
                    ws.read(buffer); // Read a message.
                    const auto message = buffer_cast<int *>(buffer.data());
                    if (*message == message_codes::k_canvas_size){
                        auto w = (int)message[1];
                        auto h = (int)message[2];
                        m_canvas_size = {w, h};
                    }else if (*message == message_codes::k_left_mouse_down) {
                        m_server_engine->m_mouse_input->register_mouse_down(
                            mouse_buttons::left);
                    }else if (*message == message_codes::k_right_mouse_down) {
                        m_server_engine->m_mouse_input->register_mouse_down(
                            mouse_buttons::right);
                    }else if (*message == message_codes::k_mouse_position) {
                        auto x = message[1] / net_constants::k_float_precision;
                        auto y = message[2] / net_constants::k_float_precision;
                        m_mouse_position = {x, y};
                    }else if (*message == message_codes::k_frame_finished) {
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
    
    void user_connection::send_image_draw_instruction(WebSocket &ws,
                                                      std::string_view
                                                      image_name,
                                                      rectf destination){
        send_image_draw_instruction(ws, jod::hash(image_name), destination);
    }
    
    void user_connection::send_image_draw_instruction(WebSocket &ws,
                                                      int image_name_hash,
                                                      rectf destination){
        auto msg_code = message_codes::k_draw_image_instr;
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
    
    void user_connection::send_text_draw_instruction(WebSocket &ws,
                                                     std::string_view text,
                                                     pointf position) {
        auto msg_code = message_codes::k_draw_string_instr;
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
    
    void user_connection::send_present_canvas_instruction(WebSocket &ws){
        auto msg_code_present = message_codes::k_apply_buffer;
        ws.write(
            boost::asio::buffer(&msg_code_present,sizeof(msg_code_present)));
    }
    
    float user_connection::get_aspect_ratio() {
        return static_cast<float>(m_canvas_size.w) / m_canvas_size.h;
    }
}