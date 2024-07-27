// Copyright (c) 2024 Andreas Åkerberg.

#include "Net.h"

#include "Core.h"
#include <emscripten/websocket.h>

namespace jod
{
    namespace
    {
        EM_BOOL OnOpen(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent,
                       void *userData);

        EM_BOOL OnError(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent,
                        void *userData);

        EM_BOOL OnClose(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent,
                        void *userData);

        EM_BOOL OnMessage(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent,
                          void *userData);

        int ReadFourBytesAsInt(unsigned char *bytes);

        float ReadFourBytesAsFloat(unsigned char *bytes);
    }

    void WebSocketClient::Start()
    {
        /* Check support exists. */
        if (!emscripten_websocket_is_supported())
            return;

        /* Create address to connect to. */
        auto serverAddress = "ws://" + k_host + ":" + std::to_string(k_port);

        /* Create attributes. */
        auto wsAttrs = EmscriptenWebSocketCreateAttributes{serverAddress.c_str(), NULL, EM_TRUE};

        /* Create the web socket and connect. */
        auto ws = emscripten_websocket_new(&wsAttrs);

        /* Setup callback functions. */
        emscripten_websocket_set_onopen_callback(ws, NULL, OnOpen);
        emscripten_websocket_set_onerror_callback(ws, NULL, OnError);
        emscripten_websocket_set_onclose_callback(ws, NULL, OnClose);
        emscripten_websocket_set_onmessage_callback(ws, NULL, OnMessage);
    }

    void WebSocketClient::SendMessage(std::string message)
    {
        if (message == "Tick")
        {
            int msg = MessageCodes::k_tick;
            emscripten_websocket_send_binary(m_webSocketEvent->socket, &msg, sizeof(msg));
        }
        else if (message == "Click")
        {
            int msg = MessageCodes::k_click;
            emscripten_websocket_send_binary(m_webSocketEvent->socket, &msg, sizeof(msg));
        }
        else
        {
            /* Send message and check success. */
            if (auto result =
                    emscripten_websocket_send_utf8_text(m_webSocketEvent->socket, message.c_str()))
                std::cout << "Failed to emscripten_websocket_send_utf8_text(): " << result;
        }
    }

    void NetMessageProcessor::ProcessMessage(unsigned char *bytes)
    {
        /* The first bytes contains the message code. */
        auto messageCode = ReadFourBytesAsInt(bytes);

        /* Perform corresponding action. */
        switch (messageCode)
        {
        case MessageCodes::k_drawImageInstr:
        {
            /* Next 4 bytes contains the image name hash code. */
            auto imageNameHash = ReadFourBytesAsInt(bytes + 4);

            /* Next 4 bytes contains the x coordinate. */
            auto x = ReadFourBytesAsFloat(bytes + 8);

            /* Next 4 bytes contains the y coordinate. */
            auto y = ReadFourBytesAsFloat(bytes + 12);

            /* Next 4 bytes contains the width. */
            auto w = ReadFourBytesAsFloat(bytes + 16);

            /* Next 4 bytes contains the height. */
            auto h = ReadFourBytesAsFloat(bytes + 20);

            /* Add the complete instruction. */
            _<RenderInstructionsManager>().AddImageDrawInstruction(imageNameHash, {x, y, w, h});

            break;
        }
        case MessageCodes::k_applyBuffer:
        {
            /* Apply the buffered render instructions. */
            _<RenderInstructionsManager>().ApplyBuffer();

            break;
        }
        }
    }

    namespace
    {
        EM_BOOL OnOpen(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent,
                       void *userData)
        {
            /* Save web socket event to WebSocketClient so it can be used from that object by its
             * own. */
            _<WebSocketClient>().m_webSocketEvent =
                std::shared_ptr<const EmscriptenWebSocketOpenEvent>(websocketEvent);

            std::cout << "Opening new connection.\n";

            /* Send initial message and check result. */
            if (auto result = emscripten_websocket_send_utf8_text(websocketEvent->socket,
                                                                  "Initialize connection"))
                std::cout << "Failed to send init message to server: " << result << std::endl;

            return EM_TRUE;
        }

        EM_BOOL OnError(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent,
                        void *userData)
        {
            /* Notify on web socket errors. */
            std::cout << "Web socket error.\n";

            return EM_TRUE;
        }

        EM_BOOL OnClose(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent,
                        void *userData)
        {
            /* Notify on closing web socket connection. */
            std::cout << "Closing web socket connection.\n";

            return EM_TRUE;
        }

        EM_BOOL OnMessage(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent,
                          void *userData)
        {
            /* Process the raw message data in bytes. */
            _<NetMessageProcessor>().ProcessMessage(websocketEvent->data);

            return EM_TRUE;
        }

        int ReadFourBytesAsInt(unsigned char *bytes)
        {
            /* Pick out the separate bytes. */
            auto b0 = (int)bytes[0];
            auto b1 = (int)bytes[1];
            auto b2 = (int)bytes[2];
            auto b3 = (int)bytes[3];

            /* Shift the bytes to form an integer. */
            auto result = (b3 << 3 * 8) + (b2 << 2 * 8) + (b1 << 8) + b0;

            return result;
        }

        float ReadFourBytesAsFloat(unsigned char *bytes)
        {
            /* Pick out the separate bytes. */
            auto b0 = (int)bytes[0];
            auto b1 = (int)bytes[1];
            auto b2 = (int)bytes[2];
            auto b3 = (int)bytes[3];

            /* Shift the bytes to form an integer, then divide it with 10000.0 to get a float with 4
             * decimals precision. */
            auto result =
                ((b3 << 3 * 8) + (b2 << 2 * 8) + (b1 << 8) + b0) / NetConstants::k_floatPrecision;

            return result;
        }
    }
}