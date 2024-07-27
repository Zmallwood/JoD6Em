// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
    class WebSocketClient
    {
      public:
        void Start();
        void SendMessage(std::string message);

        std::shared_ptr<const EmscriptenWebSocketOpenEvent> m_webSocketEvent;

      private:
        const std::string k_host = "localhost";
        const int k_port = 8765;
    };
}