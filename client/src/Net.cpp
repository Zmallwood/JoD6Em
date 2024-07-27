// Copyright (c) 2024 Andreas Åkerberg.

#include "Net.h"
#include "Core.h"

namespace jod
{
    EM_BOOL onopen(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent, void *userData)
    {
        _<WebSocketClient>().m_webSocketEvent = std::shared_ptr<const EmscriptenWebSocketOpenEvent>(websocketEvent);

        std::cout << "Opening new connection.\n";

        if (auto result = emscripten_websocket_send_utf8_text(websocketEvent->socket, "Initialize connection"))
            std::cout << "Failed to send init message to server: " << result << std::endl;

        return EM_TRUE;
    }

    EM_BOOL onerror(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent, void *userData)
    {
        std::cout << "Web socket error.\n";

        return EM_TRUE;
    }

    EM_BOOL onclose(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent, void *userData)
    {
        std::cout << "Closing web socket connection.\n";

        return EM_TRUE;
    }

    EM_BOOL onmessage(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent, void *userData)
    {
        const auto k_drawImageInstr = 1;
        const auto k_drawPresentCanvas = 2;

        auto b0 = (int)websocketEvent->data[0];
        auto b1 = (int)websocketEvent->data[1];
        auto b2 = (int)websocketEvent->data[2];
        auto b3 = (int)websocketEvent->data[3];

        auto i = (b3 << 3 * 8) + (b2 << 2 * 8) + (b1 << 8) + b0;

        if (i == k_drawImageInstr)
        {
            auto b4 = (int)websocketEvent->data[4];
            auto b5 = (int)websocketEvent->data[5];
            auto b6 = (int)websocketEvent->data[6];
            auto b7 = (int)websocketEvent->data[7];

            auto imageNameHash = (b7 << 3 * 8) + (b6 << 2 * 8) + (b5 << 8) + b4;

            auto b8 = (int)websocketEvent->data[8];
            auto b9 = (int)websocketEvent->data[9];
            auto b10 = (int)websocketEvent->data[10];
            auto b11 = (int)websocketEvent->data[11];

            auto x = ((b11 << 3 * 8) + (b10 << 2 * 8) + (b9 << 8) + b8) / 10000.0f;

            auto b12 = (int)websocketEvent->data[12];
            auto b13 = (int)websocketEvent->data[13];
            auto b14 = (int)websocketEvent->data[14];
            auto b15 = (int)websocketEvent->data[15];

            auto y = ((b15 << 3 * 8) + (b14 << 2 * 8) + (b13 << 8) + b12) / 10000.0f;

            auto b16 = (int)websocketEvent->data[16];
            auto b17 = (int)websocketEvent->data[17];
            auto b18 = (int)websocketEvent->data[18];
            auto b19 = (int)websocketEvent->data[19];

            auto w = ((b19 << 3 * 8) + (b18 << 2 * 8) + (b17 << 8) + b16) / 10000.0f;

            auto b20 = (int)websocketEvent->data[20];
            auto b21 = (int)websocketEvent->data[21];
            auto b22 = (int)websocketEvent->data[22];
            auto b23 = (int)websocketEvent->data[23];

            auto h = ((b23 << 3 * 8) + (b22 << 2 * 8) + (b21 << 8) + b20) / 10000.0f;

            _<Canvas>().AddImageDrawInstruction(imageNameHash, {x, y, w, h});
        }
        else if (i == k_drawPresentCanvas)
        {
            _<Canvas>().PresentNewCanvas();
        }

        return EM_TRUE;
    }

    void WebSocketClient::Start()
    {
        if (!emscripten_websocket_is_supported())
            return;

        auto server_address = "ws://" + k_host + ":" + std::to_string(k_port);

        EmscriptenWebSocketCreateAttributes ws_attrs = {server_address.c_str(), NULL, EM_TRUE};

        auto ws = emscripten_websocket_new(&ws_attrs);
        emscripten_websocket_set_onopen_callback(ws, NULL, onopen);
        emscripten_websocket_set_onerror_callback(ws, NULL, onerror);
        emscripten_websocket_set_onclose_callback(ws, NULL, onclose);
        emscripten_websocket_set_onmessage_callback(ws, NULL, onmessage);
    }

    void WebSocketClient::SendMessage(std::string message)
    {
        if (auto result = emscripten_websocket_send_utf8_text(m_webSocketEvent->socket, message.c_str()))
            printf("Failed to emscripten_websocket_send_utf8_text(): %d\n", result);
    }
}