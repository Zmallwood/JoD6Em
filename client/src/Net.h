// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
    namespace MessageCodes
    {
        constexpr int k_drawImageInstr = 1;
        constexpr int k_applyBuffer = 2;
    }

    namespace NetConstants
    {
        constexpr float k_floatPrecision = 10000.0f;
    }

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

    class NetMessageProcessor
    {
      public:
        void ProcessMessage(unsigned char *bytes);
    };
}