// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
    class WebSocketServer
    {
      public:
        void Start(std::string socketAddress, std::string socketPort);
    };
}