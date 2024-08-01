// Copyright (c) 2024 Andreas Åkerberg.

#include "net.h"
#include "client.h"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

namespace jod {
    void
    web_socket_server::start(std::string socketAddress, std::string socketPort){
        auto const address = net::ip::make_address(socketAddress);
        auto const port =
            static_cast<unsigned short>(std::atoi(socketPort.c_str()));
        net::io_context ioc{1}; // The io_context is required for all I/O.
        tcp::acceptor acceptor{ioc, {address, port}}; // The acceptor receives incoming connections.
        while (true){
            tcp::socket socket{ioc}; // This will receive the new connection.
            acceptor.accept(socket); // Block until we get a connection.
            m_clients.push_back(std::make_shared<client>(std::move(socket)));
        }
    }
}