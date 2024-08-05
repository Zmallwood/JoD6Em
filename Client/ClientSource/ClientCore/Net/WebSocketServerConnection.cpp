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
        
        EM_BOOL OnOpen(
            int eventType,
            const EmscriptenWebSocketOpenEvent *webSocketEvent,
            void *userData);
        
        EM_BOOL OnError(
            int eventType,
            const EmscriptenWebSocketErrorEvent *webSocketEvent,
            void *userData);
        
        EM_BOOL OnClose(
            int eventType,
            const EmscriptenWebSocketCloseEvent *webSocketEvent,
            void *userData);
        
        EM_BOOL OnMessage(
            int eventType,
            const EmscriptenWebSocketMessageEvent *
            webSocketEvent,
            void *userData);
        
        void ProcessIncomingMessage(unsigned char *bytes);
        
        int ReadFourBytesAsInt(unsigned char *bytes);
        
        float ReadFourBytesAsFloat(unsigned char *bytes);
    }
    
    void WebSocketServerConnection::Connect() const {
        
        // Check support exists.
        if (!emscripten_websocket_is_supported()) return;
        
        // Create address to connect to.
        auto serverAddress = "ws://" + k_host + ":" + std::to_string(k_port);
        
        // Create attributes.
        auto wsAttrs = EmscriptenWebSocketCreateAttributes{
            serverAddress.c_str(), NULL, EM_TRUE};
        
        // Create the web socket and connect.
        auto ws = emscripten_websocket_new(&wsAttrs);
        
        // Setup callback functions.
        emscripten_websocket_set_onopen_callback(ws, NULL, OnOpen);
        emscripten_websocket_set_onerror_callback(ws, NULL, OnError);
        emscripten_websocket_set_onclose_callback(ws, NULL, OnClose);
        emscripten_websocket_set_onmessage_callback(ws, NULL, OnMessage);
    }
    
    void WebSocketServerConnection::SendMessage(int messageType) const {
        
        // Determine message type to be sent.
        switch (messageType){
        
        // Send canvas size to server.
        case MessageCodes::k_canvasSize: {
            
            // Get canvas size in pixels.
            auto canvasSize = GetCanvasSize();
            
            int msg[3];
            
            // Fill data with message type and canvas size dimensions.
            msg[0] = MessageCodes::k_canvasSize;
            msg[1] = canvasSize.w;
            msg[2] = canvasSize.h;
            
            // Try send packet and handle failure.
            if (auto result =
                    emscripten_websocket_send_binary(
                        m_webSocketEvent->socket,
                        msg, 3 * sizeof(int))) {
                
                std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                    result;
            }
            
            break;
        }
        case MessageCodes::k_leftMouseDown: {
            
            // Message contains only message code.
            int msg = MessageCodes::k_leftMouseDown;
            
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_webSocketEvent->socket,
                    &msg,
                    sizeof(msg))) {
                
                std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                    result;
            }
            
            break;
        }
        case MessageCodes::k_rightMouseDown: {
            
            // Message contains only message code.
            int msg = MessageCodes::k_rightMouseDown;
            
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_webSocketEvent->socket,
                    &msg,
                    sizeof(msg))) {
                
                std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                    result;
            }
            
            break;
        }
        case MessageCodes::k_mousePosition: {
            
            auto mousePosition = GetMousePosition();
            
            int msg[3];
            
            msg[0] = MessageCodes::k_mousePosition;
            msg[1] = (int)(mousePosition.x * net_constants::k_floatPrecision);
            msg[2] = (int)(mousePosition.y * net_constants::k_floatPrecision);
            
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_webSocketEvent->socket,
                    &msg,
                    sizeof(msg))) {
                
                std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                    result;
            }
            
            break;
        }
        case MessageCodes::k_frameFinished: {
            
            int msg = MessageCodes::k_frameFinished;
            
            // Try send packet and handle failure.
            if (auto result = emscripten_websocket_send_binary(
                    m_webSocketEvent->socket,
                    &msg,
                    sizeof(msg))) {
                
                std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                    result;
            }
            break;
        }
        }
    }
    
    namespace {
        
        EM_BOOL OnOpen(
            int eventType,
            const EmscriptenWebSocketOpenEvent *webSocketEvent,
            void *userData){
            
            // Save web socket event to WebSocketClient so it can be used from that object by its own.
            _<WebSocketServerConnection>().m_webSocketEvent =
                std::shared_ptr<const EmscriptenWebSocketOpenEvent>(
                    webSocketEvent);
            
            std::cout << "Opening new connection.\n";
            
            // Send initial message and check result.
            if (auto result = emscripten_websocket_send_utf8_text(
                    webSocketEvent->socket,
                    "Initialize connection")) {
                
                std::cout << "Failed to send init message to server: " <<
                    result << std::endl;
            }
            
            // Send canvas size immediately to server.
            _<WebSocketServerConnection>().SendMessage(
                MessageCodes::k_canvasSize);
            
            return EM_TRUE;
        }
        
        EM_BOOL OnError(
            int eventType,
            const EmscriptenWebSocketErrorEvent *webSocketEvent,
            void *userData){
            
            // Notify on web socket errors.
            std::cout << "Web socket error.\n";
            
            return EM_TRUE;
        }
        
        EM_BOOL OnClose(
            int eventType,
            const EmscriptenWebSocketCloseEvent *webSocketEvent,
            void *userData){
            
            // Notify on closing web socket connection.
            std::cout << "Closing web socket connection.\n";
            
            return EM_TRUE;
        }
        
        EM_BOOL OnMessage(
            int eventType,
            const EmscriptenWebSocketMessageEvent *
            webSocketEvent,
            void *userData){
            
            // Process the raw message data in bytes.
            ProcessIncomingMessage(webSocketEvent->data);
            
            return EM_TRUE;
        }
        
        void ProcessIncomingMessage(unsigned char *bytes) {
            
            // The first bytes contains the message code.
            auto messageCode = ReadFourBytesAsInt(bytes);
            
            // Perform corresponding action.
            switch (messageCode){
            
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
                _<RenderInstrutionsManager>().AddImageDrawInstruction(
                    imageNameHash, {x, y, w, h});
                
                break;
            }
            case MessageCodes::k_applyBuffer: {
                
                _<RenderInstrutionsManager>().ApplyBuffer(); // Apply the buffered render instructions.
                
                break;
            }
            case MessageCodes::k_drawStringInstr: {
                
                auto x = ReadFourBytesAsFloat(bytes + 4);
                auto y = ReadFourBytesAsFloat(bytes + 8);
                auto length = ReadFourBytesAsInt(bytes + 12);
                
                std::string str;
                
                for (auto i = 0; i < length; i++) {
                    auto c = ReadFourBytesAsInt(bytes + 16 + i*4);
                    str += (char)c;
                }
                
                _<RenderInstrutionsManager>().AddTextDrawInstruction(
                    str,
                    {x,y});
                
                break;
            }
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
                          net_constants::k_floatPrecision;
            
            return result;
        }
    }
}