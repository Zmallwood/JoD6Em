// Copyright (c) 2024 Andreas Åkerberg.

#include "Net.h"

#include "Client.h"

namespace net = boost::asio;

using tcp = boost::asio::ip::tcp;

namespace jod
{
    void WebSocketServer::Start(std::string socketAddress, std::string socketPort)
    {
        auto const address = net::ip::make_address(socketAddress);
        auto const port = static_cast<unsigned short>(std::atoi(socketPort.c_str()));

        /* The io_context is required for all I/O. */

        net::io_context ioc{1};

        /* The acceptor receives incoming connections. */

        tcp::acceptor acceptor{ioc, {address, port}};

        while (true)
        {
            /* This will receive the new connection. */

            tcp::socket socket{ioc};

            /* Block until we get a connection. */

            acceptor.accept(socket);

            std::cout << "Connection opened.\n";

            m_clients.push_back(std::make_shared<Client>(std::move(socket)));
        }
    }
}