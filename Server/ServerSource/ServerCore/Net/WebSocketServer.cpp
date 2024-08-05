/*
 * WebSocketServer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "WebSocketServer.hpp"
#include "UserConnection.hpp"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

namespace JoD {
    
    void WebSocketServer::Run(
        std::string_view socketAddress,
        std::string_view socketPort) {
        
        auto const address = net::ip::make_address(socketAddress);
        auto const port =
            static_cast<unsigned short>(std::atoi(socketPort.data()));
        
        // The io_context is required for all I/O.
        net::io_context ioc{1};
        
        // The acceptor receives incoming connections.
        tcp::acceptor acceptor{ioc, {address, port}};
        
        while (true){
            
            // This will receive the new connection.
            tcp::socket socket{ioc};
            
            // Block until we get a connection.
            acceptor.accept(socket);
            
            m_userConnections.push_back(
                std::make_shared<UserConnection>(
                    std::move(socket)));
        }
    }
}