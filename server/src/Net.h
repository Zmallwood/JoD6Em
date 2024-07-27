#pragma once

namespace jod
{
    class WebSocketServer
    {
      public:
        void Start(std::string socketAddress, std::string socketPort);
    };
}