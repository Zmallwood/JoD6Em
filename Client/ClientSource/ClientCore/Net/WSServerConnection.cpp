/*
 * WSServerConnection.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "WSServerConnection.hpp"
#include "ClientCore/DrawInstructions/DrawInstrMngr.hpp"
#include "MessageCodes.hpp"
#include "ClientCore/Assets/ImageBank.hpp"

namespace JoD {
namespace {
// Callback for opening new connection.
    EM_BOOL OnOpen(
        int eventType,
        const EmscriptenWebSocketOpenEvent *webSocketEvent,
        void *userData);
// Callback for error occurring.
    EM_BOOL OnError(
        int eventType,
        const EmscriptenWebSocketErrorEvent *webSocketEvent,
        void *userData);
// Callback for connection closing.
    EM_BOOL OnClose(
        int eventType,
        const EmscriptenWebSocketCloseEvent *webSocketEvent,
        void *userData);
// Callback for message recieved.
    EM_BOOL OnMessage(
        int eventType,
        const EmscriptenWebSocketMessageEvent *
        webSocketEvent,
        void *userData);
// Process a message recieved from server.
    void ProcessIncomingMessage(unsigned char *bytes);
// Convert four bytes into an integer.
    int ReadFourBytesAsInt(unsigned char *bytes);
// Convert four bytes into a float.
    float ReadFourBytesAsFloat(unsigned char *bytes);
}

void WSServerConnection::Connect() const {
// Check support exists.
    if (!emscripten_websocket_is_supported())
        return;
// Create address to connect to.
    const auto serverAddress = "ws://" + k_host + ":" +
                               std::to_string(k_port);
// Create attributes.
    auto wsAttrs = EmscriptenWebSocketCreateAttributes{
        serverAddress.c_str(), NULL, EM_TRUE};
// Create the web socket and connect.
    const auto webSocket = emscripten_websocket_new(&wsAttrs);
// Setup callback functions.
    emscripten_websocket_set_onopen_callback(webSocket, nullptr, OnOpen);
    emscripten_websocket_set_onerror_callback(webSocket, nullptr, OnError);
    emscripten_websocket_set_onclose_callback(webSocket, nullptr, OnClose);
    emscripten_websocket_set_onmessage_callback(
        webSocket, nullptr,
        OnMessage);
}


void WSServerConnection::SendMessage(const int *data,
                                     int length) const {
// Try send packet and handle failure.
    if (auto result =
            emscripten_websocket_send_binary(
                m_webSocketEvent->socket,
                (void*)data, length*sizeof(int))) {
        std::cout << "Failed to emscripten_websocket_send_binary(): " <<
            result;
    }
}
void WSServerConnection::SendMessage(int messageType) const {
// Determine message type to be sent.
    switch (messageType){
// Send canvas size to server.
    case MessageCodes::k_canvasSize: {
// Get canvas size in pixels.
        auto canvasSize = GetCanvasSize();
        int data[3];
// Fill data with message type and canvas size dimensions.
        data[0] = MessageCodes::k_canvasSize;
        data[1] = canvasSize.w;
        data[2] = canvasSize.h;
// Try send packet and handle failure.
        if (auto result =
                emscripten_websocket_send_binary(
                    m_webSocketEvent->socket,
                    data, 3 * sizeof(int))) {
            std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                result;
        }
        break;
    }
    case MessageCodes::k_leftMouseDown: {
// Message contains only message code.
        int data = MessageCodes::k_leftMouseDown;
// Try send packet and handle failure.
        if (auto result = emscripten_websocket_send_binary(
                m_webSocketEvent->socket,
                &data,
                sizeof(data))) {
            std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                result;
        }
        break;
    }
    case MessageCodes::k_leftMouseUp: {
// Message contains only message code.
        int data = MessageCodes::k_leftMouseUp;
// Try send packet and handle failure.
        if (auto result = emscripten_websocket_send_binary(
                m_webSocketEvent->socket,
                &data,
                sizeof(data))) {
            std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                result;
        }
        break;
    }
    case MessageCodes::k_rightMouseUp: {
// Message contains only message code.
        int data = MessageCodes::k_rightMouseUp;
// Try send packet and handle failure.
        if (auto result = emscripten_websocket_send_binary(
                m_webSocketEvent->socket,
                &data,
                sizeof(data))) {
            std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                result;
        }
        break;
    }
    case MessageCodes::k_rightMouseDown: {
// Message contains only message code.
        int data = MessageCodes::k_rightMouseDown;
// Try send packet and handle failure.
        if (auto result = emscripten_websocket_send_binary(
                m_webSocketEvent->socket,
                &data,
                sizeof(data))) {
            std::cout << "Failed to emscripten_websocket_send_binary(): " <<
                result;
        }
        break;
    }
    case MessageCodes::k_mousePosition: {
        auto mousePosition = GetMousePosition();
        int data[3];
        data[0] = MessageCodes::k_mousePosition;
        data[1] = (int)(mousePosition.x * NetConstants::k_floatPrecision);
        data[2] = (int)(mousePosition.y * NetConstants::k_floatPrecision);
// Try send packet and handle failure.
        if (auto result = emscripten_websocket_send_binary(
                m_webSocketEvent->socket,
                &data,
                sizeof(data))) {
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
        void *userData) {
// Save web socket event to WebSocketClient so it can be used from that object by its own.
        _<WSServerConnection>().SetWebSocketEvent(
            std::unique_ptr<const EmscriptenWebSocketOpenEvent>(
                webSocketEvent));
        std::cout << "Opening new connection.\n";
// Send initial message and check result.
        if (auto result = emscripten_websocket_send_utf8_text(
                webSocketEvent->socket,
                "Initialize connection")) {
            std::cout << "Failed to send init message to server: " <<
                result << std::endl;
        }
// Send canvas size immediately to server.
        _<WSServerConnection>().SendMessage(
            MessageCodes::k_canvasSize);
        return EM_TRUE;
    }
    
    EM_BOOL OnError(
        int eventType,
        const EmscriptenWebSocketErrorEvent *webSocketEvent,
        void *userData) {
// Notify on web socket errors.
        std::cout << "Web socket error.\n";
        return EM_TRUE;
    }
    
    EM_BOOL OnClose(
        int eventType,
        const EmscriptenWebSocketCloseEvent *webSocketEvent,
        void *userData) {
// Notify on closing web socket connection.
        std::cout << "Closing web socket connection.\n";
        return EM_TRUE;
    }
    
    EM_BOOL OnMessage(
        int eventType,
        const EmscriptenWebSocketMessageEvent *
        webSocketEvent,
        void *userData) {
// Process the raw message data in bytes.
        ProcessIncomingMessage(webSocketEvent->data);
        return EM_TRUE;
    }
    
    void ProcessIncomingMessage(unsigned char *bytes) {
// The first bytes contains the message code.
        auto messageCode = ReadFourBytesAsInt(bytes);
// Perform corresponding action.
        switch (messageCode){
        case MessageCodes::k_drawImageInstruction: {
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
            _<DrawInstrMngr>().AddImageDrawInst(
                imageNameHash, {x, y, w, h}, false);
            break;
        }
        case MessageCodes::k_drawImageRepeatInstruction: {
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
            auto textureFillW = ReadFourBytesAsFloat(bytes + 24);
            auto textureFillH = ReadFourBytesAsFloat(bytes + 28);
// Add the complete instruction.
            _<DrawInstrMngr>().AddImageDrawInst(
                imageNameHash, {x, y, w, h}, true,
                {textureFillW, textureFillH});
            break;
        }
        case MessageCodes::k_applyBuffer: {
// Apply the buffered render instructions.
            _<DrawInstrMngr>().ApplyBuffer();
            break;
        }
        case MessageCodes::k_drawStringInstruction: {
// Next four bytes contain the x position.
            auto x = ReadFourBytesAsFloat(bytes + 4);
// Next for bytes contain the y position.
            auto y = ReadFourBytesAsFloat(bytes + 8);
// Next for bytes contain the centerAlign state.
            auto centerAlign = ReadFourBytesAsInt(bytes + 12) !=
                               0 ? true : false;
// Next for bytes contain the length of the string to draw.
            auto length = ReadFourBytesAsInt(bytes + 16);
// To hold the recieved text string.
            std::string str;
// Get the character from the incoming message and add to the resulting
// string object.
            for (auto i = 0; i < length; i++) {
// Get the char code.
                auto c = ReadFourBytesAsInt(bytes + 20 + i*4);
// Cast to char and append to resulting string object.
                str += (char)c;
            }
// Add new text draw instruction with the collected data.
            _<DrawInstrMngr>().AddTextDrawInstr(
                str,
                {x,y},
                centerAlign);
            break;
        }
        case MessageCodes::k_requestImageDimensions: {
// Next four bytes contain the image name hash code.
            auto imageNameHash = ReadFourBytesAsInt(bytes + 4);
// Get the image dimensions for the obtain image name hash code.
            auto dimensions =
                _<ImageBank>().GetImageDimensions(imageNameHash);
// Prepare a new message for returning the dimensions result.
            int data[4];
// Fill data with message type and canvas size dimensions.
            data[0] = MessageCodes::k_provideImageDimensions;
            data[1] = imageNameHash;
            data[2] = dimensions.w;
            data[3] = dimensions.h;
// Send the message to server.
            _<WSServerConnection>().SendMessage(data, 4);
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
        auto result =
            ((b3 << 3 * 8)
             + (b2 << 2 * 8)
             + (b1 << 8) + b0) /
            NetConstants::k_floatPrecision;
        return result;
    }
}
}
