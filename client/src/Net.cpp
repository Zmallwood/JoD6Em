// Copyright (c) 2024 Andreas Åkerberg.
#include "Net.h"
#include "Core.h"
#include "MessageCodes.h"
#include "NetConfiguration.h"
#include "Util.h"

namespace jod {
    namespace {
        EM_BOOL OnOpen(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent,
                       void *userData);
        EM_BOOL OnError(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent,
                        void *userData);
        EM_BOOL OnClose(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent,
                        void *userData);
        EM_BOOL OnMessage(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent,
                          void *userData);
        void ProcessIncomingMessage(unsigned char *bytes);
        int ReadFourBytesAsInt(unsigned char *bytes);
        float ReadFourBytesAsFloat(unsigned char *bytes);
    }
    void
    WebSocketServerConnection::Connect(){
        if (!emscripten_websocket_is_supported()) return; // Check support exists.
        // Create address to connect to.
        auto serverAddress = "ws://" + k_host + ":" + std::to_string(k_port);
        // Create attributes.
        auto wsAttrs = EmscriptenWebSocketCreateAttributes{serverAddress.c_str(), NULL, EM_TRUE};
        auto ws = emscripten_websocket_new(&wsAttrs); // Create the web socket and connect.
        // Setup callback functions.
        emscripten_websocket_set_onopen_callback(ws, NULL, OnOpen);
        emscripten_websocket_set_onerror_callback(ws, NULL, OnError);
        emscripten_websocket_set_onclose_callback(ws, NULL, OnClose);
        emscripten_websocket_set_onmessage_callback(ws, NULL, OnMessage);
    }
    void
    WebSocketServerConnection::SendMessage(int messageType){
        switch (messageType){ // Determine message type to be sent.
        case MessageCodes::k_canvasSize: { // Send canvas size to server.
            auto canvSize = GetCanvasSize(); // Get canvas size in pixels.
            int msg[3];
            // Fill data with message type and canvas size dimensions.
            msg[0] = MessageCodes::k_canvasSize;
            msg[1] = canvSize.w;
            msg[2] = canvSize.h;
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(m_webSocketEvent->socket, msg, 3 * sizeof(int)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " << result;
            break;
        }
        case MessageCodes::k_mouseDown: {
            int msg = MessageCodes::k_mouseDown; // Message contains only message code.
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(m_webSocketEvent->socket, &msg, sizeof(msg)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " << result;
            break;
        }
        case MessageCodes::k_mousePosition: {
            auto mousePosition = GetMousePosition();
            int msg[3];
            msg[0] = MessageCodes::k_mousePosition;
            msg[1] = (int)(mousePosition.x * NetConstants::k_floatPrecision);
            msg[2] = (int)(mousePosition.y * NetConstants::k_floatPrecision);
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(m_webSocketEvent->socket, &msg, sizeof(msg)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " << result;
            break;
        }
        case MessageCodes::k_frameFinished: {
            int msg = MessageCodes::k_frameFinished;
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(m_webSocketEvent->socket, &msg, sizeof(msg)))
                std::cout << "Failed to emscripten_websocket_send_binary(): " << result;
            break;
        }
        }
    }
    namespace {
        EM_BOOL
        OnOpen(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent,
               void *userData){
            // Save web socket event to WebSocketClient so it can be used from that object by its own.
            _<WebSocketServerConnection>().m_webSocketEvent =
                std::shared_ptr<const EmscriptenWebSocketOpenEvent>(websocketEvent);
            std::cout << "Opening new connection.\n";
            // Send initial message and check result.
            if (auto result = emscripten_websocket_send_utf8_text(websocketEvent->socket,
                                                                  "Initialize connection"))
                std::cout << "Failed to send init message to server: " << result << std::endl;
            // Send canvas size immediately to server.
            _<WebSocketServerConnection>().SendMessage(MessageCodes::k_canvasSize);
            return EM_TRUE;
        }
        EM_BOOL
        OnError(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent,
                void *userData){
            std::cout << "Web socket error.\n"; // Notify on web socket errors.
            return EM_TRUE;
        }
        EM_BOOL
        OnClose(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent,
                void *userData){
            std::cout << "Closing web socket connection.\n"; // Notify on closing web socket connection.
            return EM_TRUE;
        }
        EM_BOOL
        OnMessage(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent,
                  void *userData){
            ProcessIncomingMessage(websocketEvent->data); // Process the raw message data in bytes.
            return EM_TRUE;
        }
        void
        ProcessIncomingMessage(unsigned char *bytes){
            auto messageCode = ReadFourBytesAsInt(bytes); // The first bytes contains the message code.
            switch (messageCode){ // Perform corresponding action.
            case MessageCodes::k_drawImageInstr: {
                // Next 4 bytes contains the image name hash code.
                auto imageNameHash = ReadFourBytesAsInt(bytes + 4);
                // Next 4 bytes contains the x coordinate.
                auto x = ReadFourBytesAsFloat(bytes + 8);
                // Next 4 bytes contains the y coordinate.
                auto y = ReadFourBytesAsFloat(bytes + 12);
                // Next 4 bytes contains the width.
                auto w = ReadFourBytesAsFloat(bytes + 16);
                // Next 4 bytes contains the height.
                auto h = ReadFourBytesAsFloat(bytes + 20);
                // Add the complete instruction.
                _<RenderInstructionsManager>().AddImageDrawInstruction(imageNameHash, {x, y, w, h});
                break;
            }
            case MessageCodes::k_applyBuffer: {
                _<RenderInstructionsManager>().ApplyBuffer(); // Apply the buffered render instructions.
                break;
            }
            }
        }
        int
        ReadFourBytesAsInt(unsigned char *bytes){
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
        ReadFourBytesAsFloat(unsigned char *bytes){
            // Pick out the separate bytes.
            auto b0 = (int)bytes[0];
            auto b1 = (int)bytes[1];
            auto b2 = (int)bytes[2];
            auto b3 = (int)bytes[3];
            // Shift the bytes to form an integer, then divide it with 10000.0 to get a float with 4
            // decimals precision.
            auto result =
                ((b3 << 3 * 8) + (b2 << 2 * 8) + (b1 << 8) + b0) / NetConstants::k_floatPrecision;
            return result;
        }
    }
}