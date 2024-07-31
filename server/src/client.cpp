// Copyright (c) 2024 Andreas Åkerberg.
#include "client.h"
#include "net.h"
#include "client_core.h"
#include "message_codes.h"
#include "net_configuration.h"
#include "player.h"
#include "scene_components.h"
#include "cursor.h"
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
using tcp = boost::asio::ip::tcp;
namespace jod {
    client::client(tcp::socket socket)
        : m_serverEngine(std::make_shared<server_engine>(*this)),
        m_player(std::make_shared<player>()),
        m_tileHovering(std::make_shared<tile_hovering>(*this)),
        m_mouseMovement(std::make_shared<mouse_movement>(*this)),
        m_cursor(std::make_shared<cursor>(*this)){
        std::thread(
            &client::do_session,
            this,
            std::move(socket)).detach();
    }
    void
    client::do_session(tcp::socket socket){
        try{
            // Construct the stream by moving in the socket.
            websocket::stream<tcp::socket> ws{std::move(socket)};
            // Set a decorator to change the Server of the handshake.
            ws.set_option(
                websocket::stream_base::decorator(
                    [](websocket::response_type &res){
                res.set(http::field::server,
                        std::string(BOOST_BEAST_VERSION_STRING) + " websocket-server-sync");
            }));
            ws.accept(); // Accept the websocket handshake.
            ws.text(false); // Receive binary data, not text.
            while (true){
                m_serverEngine->update();
                m_serverEngine->render(ws);
                while (true){
                    beast::flat_buffer buffer; // This buffer will hold the incoming message.
                    ws.read(buffer); // Read a message.
                    const auto message = buffer_cast<int *>(buffer.data());
                    if (*message == message_codes::k_canvasSize){
                        auto w = (int)message[1];
                        auto h = (int)message[2];
                        m_canvasSize = {w, h};
                        std::cout << "Recieved canvas size: " << w << ", " << h << std::endl;
                    }else if (*message == message_codes::k_mouseDown) {
                        m_serverEngine->m_mouseInput->register_mouse_down();
                        m_serverEngine->on_mouse_down();
                    }else if (*message == message_codes::k_mousePosition) {
                        auto x = message[1] / net_constants::k_floatPrecision;
                        auto y = message[2] / net_constants::k_floatPrecision;
                        m_mousePosition = {x, y};
                    }else if (*message == message_codes::k_frameFinished) {
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
    void
    client::send_image_draw_instruction(
        websocket::stream<tcp::socket> &ws,
        std::string_view imageName,
        rectf dest){
        send_image_draw_instruction(
            ws,
            jod::hash(imageName),
            dest);
    }
    void
    client::send_image_draw_instruction(
        websocket::stream<tcp::socket> &ws,
        int imageNameHash,
        rectf dest){
        auto msg_code = message_codes::k_drawImageInstr;
        auto x = (int)(dest.x * net_constants::k_floatPrecision);
        auto y = (int)(dest.y * net_constants::k_floatPrecision);
        auto w = (int)(dest.w * net_constants::k_floatPrecision);
        auto h = (int)(dest.h * net_constants::k_floatPrecision);
        auto data = std::vector<int>();
        data.push_back(msg_code);
        data.push_back(imageNameHash);
        data.push_back(x);
        data.push_back(y);
        data.push_back(w);
        data.push_back(h);
        ws.write(boost::asio::buffer(data));
    }
    void
    client::send_present_canvas_instruction(websocket::stream<tcp::socket> &ws){
        auto msg_code_present = message_codes::k_applyBuffer;
        ws.write(boost::asio::buffer(&msg_code_present,
                                     sizeof(msg_code_present)));
    }
    float
    client::get_aspect_ratio(){
        return static_cast<float>(m_canvasSize.w) / m_canvasSize.h;
    }
}