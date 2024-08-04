/*
 * WebSocketServerConnection.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "WebSocketServerConnection.hpp"
#include "ClientCore/Instructions/RenderInstructionsManager.hpp"
#include "MessageCodes.hpp"
#include "NetConfiguration.hpp"

namespace JoD {
    namespace {
        EM_BOOL OnOpen(int event_type,
                        const EmscriptenWebSocketOpenEvent *web_socket_event,
                        void *user_data);
        EM_BOOL OnError(int event_type,
                         const EmscriptenWebSocketErrorEvent *web_socket_event,
                         void *user_data);
        EM_BOOL OnClose(int event_type,
                         const EmscriptenWebSocketCloseEvent *web_socket_event,
                         void *user_data);
        EM_BOOL OnMessage(int event_type,
                           const EmscriptenWebSocketMessageEvent *
                           web_socket_event,
                           void *user_data);
        void ProcessIncomingMessage(unsigned char *bytes);
        int ReadFourBytesAsInt(unsigned char *bytes);
        float ReadFourBytesAsFloat(unsigned char *bytes);
    }
    
    void WebSocketServerConnection::Connect() {
        if (!emscripten_websocket_is_supported()) return; // Check support exists.
        // Create address to connect to.
        auto server_address = "ws://" + k_host + ":" + std::to_string(k_port);
        // Create attributes.
        auto ws_attrs = EmscriptenWebSocketCreateAttributes{
            server_address.c_str(), NULL, EM_TRUE};
        auto ws = emscripten_websocket_new(&ws_attrs); // Create the web socket and connect.
        // Setup callback functions.
        emscripten_websocket_set_onopen_callback(ws, NULL, OnOpen);
        emscripten_websocket_set_onerror_callback(ws, NULL, OnError);
        emscripten_websocket_set_onclose_callback(ws, NULL, OnClose);
        emscripten_websocket_set_onmessage_callback(ws, NULL, OnMessage);
    }
    
    void WebSocketServerConnection::SendMessage(int message_type) {
        switch (message_type){ // Determine message type to be sent.
        case MessageCodes::k_canvas_size: { // Send canvas size to server.
            auto canvas_size = GetCanvasSize(); // Get canvas size in pixels.
            int msg[3];
            // Fill data with message type and canvas size dimensions.
            msg[0] = MessageCodes::k_canvas_size;
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
        case MessageCodes::k_left_mouse_down: {
            int msg = MessageCodes::k_left_mouse_down; // Message contains only message code.
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_web_socket_event->socket,
                    &msg,
                    sizeof(msg)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                    result;
            break;
        }
        case MessageCodes::k_right_mouse_down: {
            int msg = MessageCodes::k_right_mouse_down; // Message contains only message code.
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_web_socket_event->socket,
                    &msg,
                    sizeof(msg)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                    result;
            break;
        }
        case MessageCodes::k_mouse_position: {
            auto mouse_position = GetMousePosition();
            int msg[3];
            msg[0] = MessageCodes::k_mouse_position;
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
        case MessageCodes::k_frame_finished: {
            int msg = MessageCodes::k_frame_finished;
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
        EM_BOOL OnOpen(int event_type,
                        const EmscriptenWebSocketOpenEvent *web_socket_event,
                        void *user_data){
            // Save web socket event to WebSocketClient so it can be used from that object by its own.
            _<WebSocketServerConnection>().m_web_socket_event =
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
            _<WebSocketServerConnection>().SendMessage(
                MessageCodes::k_canvas_size);
            return EM_TRUE;
        }
        
        EM_BOOL OnError(int event_type,
                         const EmscriptenWebSocketErrorEvent *web_socket_event,
                         void *user_data){
            std::cout << "Web socket error.\n"; // Notify on web socket errors.
            return EM_TRUE;
        }
        
        EM_BOOL OnClose(int event_type,
                         const EmscriptenWebSocketCloseEvent *web_socket_event,
                         void *user_data){
            std::cout << "Closing web socket connection.\n"; // Notify on closing web socket connection.
            return EM_TRUE;
        }
        
        EM_BOOL OnMessage(int event_type,
                           const EmscriptenWebSocketMessageEvent *
                           web_socket_event,
                           void *user_data){
            ProcessIncomingMessage(web_socket_event->data); // Process the raw message data in bytes.
            return EM_TRUE;
        }
        
        void ProcessIncomingMessage(unsigned char *bytes) {
            auto message_code = ReadFourBytesAsInt(bytes); // The first bytes contains the message code.
            switch (message_code){ // Perform corresponding action.
            case MessageCodes::k_draw_image_instr: {
                // Next 4 bytes contains the image name hash code.
                auto image_name_hash = ReadFourBytesAsInt(bytes + 4);
                // Next 4 bytes contains the x coordinate.
                auto x = ReadFourBytesAsFloat(bytes + 8);
                // Next 4 bytes contains the y coordinate.
                auto y = ReadFourBytesAsFloat(bytes + 12);
                // Next 4 bytes contains the width.
                auto w = ReadFourBytesAsFloat(bytes + 16);
                // Next 4 bytes contains the height.
                auto h = ReadFourBytesAsFloat(bytes + 20);
                // Add the complete instruction.
                _<RenderInstrutionsManager>().AddImageDrawInstruction(
                    image_name_hash, {x, y, w, h});
                break;
            }
            case MessageCodes::k_apply_buffer: {
                _<RenderInstrutionsManager>().ApplyBuffer(); // Apply the buffered render instructions.
                break;
            }
            case MessageCodes::k_draw_string_instr:
            {
                auto x = ReadFourBytesAsFloat(bytes + 4);
                auto y = ReadFourBytesAsFloat(bytes + 8);
                auto length = ReadFourBytesAsInt(bytes + 12);
                std::string str;
                for (auto i = 0; i < length; i++) {
                    auto c = ReadFourBytesAsInt(bytes + 16 + i*4);
                    str += (char)c;
                }
                _<RenderInstrutionsManager>().AddTextDrawInstruction(str, {x,y});
            }
            break;
            }
        }
        
        int ReadFourBytesAsInt(unsigned char *bytes) {
            // Pick out the separate bytes.
            auto b0 = (int)bytes[0];
            auto b1 = (int)bytes[1];
            auto b2 = (int)bytes[2];
            auto b3 = (int)bytes[3];
            // Shift the bytes to form an integer.
            auto result = (b3 << 3 * 8) + (b2 << 2 * 8) + (b1 << 8) + b0;
            return result;
        }
        
        float ReadFourBytesAsFloat(unsigned char *bytes) {
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