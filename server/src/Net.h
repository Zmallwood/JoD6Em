// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
    class Client;

    class WebSocketServer
    {
      public:
        void Start(std::string socketAddress, std::string socketPort);

      private:
        std::vector<std::shared_ptr<Client>> m_clients;
    };
}