// Copyright (c) 2024 Andreas Åkerberg.
#include "net.h"
#include "core.h"
#include "message_codes.h"
#include "net_configuration.h"
#include "util.h"
namespace jod {
    namespace {
        EM_BOOL on_open(
            int eventType,
            const EmscriptenWebSocketOpenEvent *websocketEvent,
            void *userData);
        EM_BOOL on_error(
            int eventType,
            const EmscriptenWebSocketErrorEvent *websocketEvent,
            void *userData);
        EM_BOOL on_close(
            int eventType,
            const EmscriptenWebSocketCloseEvent *websocketEvent,
            void *userData);
        EM_BOOL on_message(
            int eventType,
            const EmscriptenWebSocketMessageEvent *websocketEvent,
            void *userData);
        void process_incoming_message(
            unsigned char *bytes);
        int read_four_bytes_as_int(
            unsigned char *bytes);
        float read_four_bytes_at_float(
            unsigned char *bytes);
    }
    void
    web_socket_server_connection::connect(){
        if (!emscripten_websocket_is_supported()) return; // Check support exists.
        // Create address to connect to.
        auto serverAddress = "ws://" + k_host + ":" + std::to_string(k_port);
        // Create attributes.
        auto wsAttrs = EmscriptenWebSocketCreateAttributes{
            serverAddress.c_str(), NULL, EM_TRUE};
        auto ws = emscripten_websocket_new(&wsAttrs); // Create the web socket and connect.
        // Setup callback functions.
        emscripten_websocket_set_onopen_callback(
            ws,
            NULL,
            on_open);
        emscripten_websocket_set_onerror_callback(
            ws,
            NULL,
            on_error);
        emscripten_websocket_set_onclose_callback(
            ws,
            NULL,
            on_close);
        emscripten_websocket_set_onmessage_callback(
            ws,
            NULL,
            on_message);
    }
    void
    web_socket_server_connection::send_message(int messageType){
        switch (messageType){ // Determine message type to be sent.
        case message_codes::k_canvasSize: { // Send canvas size to server.
            auto canvSize = get_canvas_size(); // Get canvas size in pixels.
            int msg[3];
            // Fill data with message type and canvas size dimensions.
            msg[0] = message_codes::k_canvasSize;
            msg[1] = canvSize.w;
            msg[2] = canvSize.h;
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_webSocketEvent->socket,
                    msg,
                    3 * sizeof(int)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " << result;
            break;
        }
        case message_codes::k_mouseDown: {
            int msg = message_codes::k_mouseDown; // Message contains only message code.
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_webSocketEvent->socket,
                    &msg,
                    sizeof(msg)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " << result;
            break;
        }
        case message_codes::k_mousePosition: {
            auto mousePosition = get_mouse_position();
            int msg[3];
            msg[0] = message_codes::k_mousePosition;
            msg[1] = (int)(mousePosition.x * net_constants::k_floatPrecision);
            msg[2] = (int)(mousePosition.y * net_constants::k_floatPrecision);
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_webSocketEvent->socket,
                    &msg,
                    sizeof(msg)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " << result;
            break;
        }
        case message_codes::k_frameFinished: {
            int msg = message_codes::k_frameFinished;
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_webSocketEvent->socket,
                    &msg,
                    sizeof(msg)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " << result;
            break;
        }
        }
    }
    namespace {
        EM_BOOL
        on_open(int eventType,
                const EmscriptenWebSocketOpenEvent *websocketEvent,
                void *userData){
            // Save web socket event to WebSocketClient so it can be used from that object by its own.
            _<web_socket_server_connection>().m_webSocketEvent =
                std::shared_ptr<const EmscriptenWebSocketOpenEvent>(websocketEvent);
            std::cout << "Opening new connection.\n";
            // Send initial message and check result.
            if (auto result = emscripten_websocket_send_utf8_text(
                    websocketEvent->socket,
                    "Initialize connection"))
                std::cout << "Failed to send init message to server: " << result << std::endl;
            // Send canvas size immediately to server.
            _<web_socket_server_connection>().send_message(message_codes::k_canvasSize);
            return EM_TRUE;
        }
        EM_BOOL
        on_error(int eventType,
                 const EmscriptenWebSocketErrorEvent *websocketEvent,
                 void *userData){
            std::cout << "Web socket error.\n"; // Notify on web socket errors.
            return EM_TRUE;
        }
        EM_BOOL
        on_close(int eventType,
                 const EmscriptenWebSocketCloseEvent *websocketEvent,
                 void *userData){
            std::cout << "Closing web socket connection.\n"; // Notify on closing web socket connection.
            return EM_TRUE;
        }
        EM_BOOL
        on_message(int eventType,
                   const EmscriptenWebSocketMessageEvent *websocketEvent,
                   void *userData){
            process_incoming_message(websocketEvent->data); // Process the raw message data in bytes.
            return EM_TRUE;
        }
        void
        process_incoming_message(unsigned char *bytes){
            auto messageCode = read_four_bytes_as_int(bytes); // The first bytes contains the message code.
            switch (messageCode){ // Perform corresponding action.
            case message_codes::k_drawImageInstr: {
                // Next 4 bytes contains the image name hash code.
                auto imageNameHash = read_four_bytes_as_int(bytes + 4);
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
                    imageNameHash,
                    {x, y, w, h});
                break;
            }
            case message_codes::k_applyBuffer: {
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
            auto result =
                ((b3 << 3 * 8) + (b2 << 2 * 8) + (b1 << 8) + b0) / net_constants::k_floatPrecision;
            return result;
        }
    }
}