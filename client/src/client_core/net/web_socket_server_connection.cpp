/*
 * web_socket_server_connection.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "web_socket_server_connection.h"
#include "client_core/instructions/render_instructions_manager.h"
#include "message_codes.h"
#include "net_configuration.h"

namespace jod {
    namespace {
        EM_BOOL on_open(int event_type,
                        const EmscriptenWebSocketOpenEvent *web_socket_event,
                        void *user_data);
        EM_BOOL on_error(int event_type,
                         const EmscriptenWebSocketErrorEvent *web_socket_event,
                         void *user_data);
        EM_BOOL on_close(int event_type,
                         const EmscriptenWebSocketCloseEvent *web_socket_event,
                         void *user_data);
        EM_BOOL on_message(int event_type,
                           const EmscriptenWebSocketMessageEvent *
                           web_socket_event,
                           void *user_data);
        void process_incoming_message(unsigned char *bytes);
        int read_four_bytes_as_int(unsigned char *bytes);
        float read_four_bytes_at_float(unsigned char *bytes);
    }
    
    void
    web_socket_server_connection::connect(){
        if (!emscripten_websocket_is_supported()) return; // Check support exists.
        // Create address to connect to.
        auto server_address = "ws://" + k_host + ":" + std::to_string(k_port);
        // Create attributes.
        auto ws_attrs = EmscriptenWebSocketCreateAttributes{
            server_address.c_str(), NULL, EM_TRUE};
        auto ws = emscripten_websocket_new(&ws_attrs); // Create the web socket and connect.
        // Setup callback functions.
        emscripten_websocket_set_onopen_callback(ws, NULL, on_open);
        emscripten_websocket_set_onerror_callback(ws, NULL, on_error);
        emscripten_websocket_set_onclose_callback(ws, NULL, on_close);
        emscripten_websocket_set_onmessage_callback(ws, NULL, on_message);
    }
    
    void
    web_socket_server_connection::send_message(int message_type){
        switch (message_type){ // Determine message type to be sent.
        case message_codes::k_canvas_size: { // Send canvas size to server.
            auto canvas_size = get_canvas_size(); // Get canvas size in pixels.
            int msg[3];
            // Fill data with message type and canvas size dimensions.
            msg[0] = message_codes::k_canvas_size;
            msg[1] = canvas_size.w;
            msg[2] = canvas_size.h;
            // Try send packet and handle failure.
            if (auto result =
                    emscripten_websocket_send_binary(
                        m_web_socket_event->socket,
                        msg, 3 * sizeof(int)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                    result;
            break;
        }
        case message_codes::k_mouse_down: {
            int msg = message_codes::k_mouse_down; // Message contains only message code.
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_web_socket_event->socket,
                    &msg,
                    sizeof(msg)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                    result;
            break;
        }
        case message_codes::k_mouse_position: {
            auto mouse_position = get_mouse_position();
            int msg[3];
            msg[0] = message_codes::k_mouse_position;
            msg[1] = (int)(mouse_position.x * net_constants::k_float_precision);
            msg[2] = (int)(mouse_position.y * net_constants::k_float_precision);
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_web_socket_event->socket,
                    &msg,
                    sizeof(msg)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                    result;
            break;
        }
        case message_codes::k_frame_finished: {
            int msg = message_codes::k_frame_finished;
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_web_socket_event->socket,
                    &msg,
                    sizeof(msg)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                    result;
            break;
        }
        }
    }
    
    namespace {
        EM_BOOL
        on_open(int event_type,
                const EmscriptenWebSocketOpenEvent *web_socket_event,
                void *user_data){
            // Save web socket event to WebSocketClient so it can be used from that object by its own.
            _<web_socket_server_connection>().m_web_socket_event =
                std::shared_ptr<const EmscriptenWebSocketOpenEvent>(
                    web_socket_event);
            std::cout << "Opening new connection.\n";
            // Send initial message and check result.
            if (auto result = emscripten_websocket_send_utf8_text(
                    web_socket_event->socket,
                    "Initialize connection"))
                std::cout << "Failed to send init message to server: " <<
                    result << std::endl;
            // Send canvas size immediately to server.
            _<web_socket_server_connection>().send_message(
                message_codes::k_canvas_size);
            return EM_TRUE;
        }
        
        EM_BOOL
        on_error(int event_type,
                 const EmscriptenWebSocketErrorEvent *web_socket_event,
                 void *user_data){
            std::cout << "Web socket error.\n"; // Notify on web socket errors.
            return EM_TRUE;
        }
        
        EM_BOOL
        on_close(int event_type,
                 const EmscriptenWebSocketCloseEvent *web_socket_event,
                 void *user_data){
            std::cout << "Closing web socket connection.\n"; // Notify on closing web socket connection.
            return EM_TRUE;
        }
        
        EM_BOOL
        on_message(int event_type,
                   const EmscriptenWebSocketMessageEvent *web_socket_event,
                   void *user_data){
            process_incoming_message(web_socket_event->data); // Process the raw message data in bytes.
            return EM_TRUE;
        }
        
        void
        process_incoming_message(unsigned char *bytes){
            auto message_code = read_four_bytes_as_int(bytes); // The first bytes contains the message code.
            switch (message_code){ // Perform corresponding action.
            case message_codes::k_draw_image_instr: {
                // Next 4 bytes contains the image name hash code.
                auto image_name_hash = read_four_bytes_as_int(bytes + 4);
                // Next 4 bytes contains the x coordinate.
                auto x = read_four_bytes_at_float(bytes + 8);
                // Next 4 bytes contains the y coordinate.
                auto y = read_four_bytes_at_float(bytes + 12);
                // Next 4 bytes contains the width.
                auto w = read_four_bytes_at_float(bytes + 16);
                // Next 4 bytes contains the height.
                auto h = read_four_bytes_at_float(bytes + 20);
                // Add the complete instruction.
                _<render_instructions_manager>().add_image_draw_instruction(
                    image_name_hash, {x, y, w, h});
                break;
            }
            case message_codes::k_apply_buffer: {
                _<render_instructions_manager>().apply_buffer(); // Apply the buffered render instructions.
                break;
            }
            }
        }
        
        int
        read_four_bytes_as_int(unsigned char *bytes){
            // Pick out the separate bytes.
            auto b0 = (int)bytes[0];
            auto b1 = (int)bytes[1];
            auto b2 = (int)bytes[2];
            auto b3 = (int)bytes[3];
            // Shift the bytes to form an integer.
            auto result = (b3 << 3 * 8) + (b2 << 2 * 8) + (b1 << 8) + b0;
            return result;
        }
        
        float
        read_four_bytes_at_float(unsigned char *bytes){
            // Pick out the separate bytes.
            auto b0 = (int)bytes[0];
            auto b1 = (int)bytes[1];
            auto b2 = (int)bytes[2];
            auto b3 = (int)bytes[3];
            // Shift the bytes to form an integer, then divide it with 10000.0 to get a float with 4
            // decimals precision.
            auto result = ((b3 << 3 * 8) + (b2 << 2 * 8) + (b1 <<
                                                            8) + b0) /
                          net_constants::k_float_precision;
            return result;
        }
    }
}