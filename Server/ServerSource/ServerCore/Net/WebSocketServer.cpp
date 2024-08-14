/*
 * WebSocketServer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "WebSocketServer.hpp"
#include "UserConnection.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace JoD {
    
    struct WebSocketServer::Impl {
        
        std::vector<std::unique_ptr<UserConnection>>
        userConnections; // Holds all connected users.
    };
    
    WebSocketServer::WebSocketServer()
        : m_pImpl(std::make_unique<Impl>()) {}
    
    WebSocketServer::~WebSocketServer() {}
    
    void WebSocketServer::Run(
        std::string_view socketAddress,
        std::string_view socketPort) {
        
        // Create address and port objects.
        const auto address = ip::make_address(socketAddress);
        const auto port =
            static_cast<unsigned short>(std::atoi(socketPort.data()));
        
        // The io_context is required for all I/O.
        io_context ioc{1};
        
        // The acceptor receives incoming connections.
        tcp::acceptor acceptor{ioc, {address, port}};
        
        // Loop until program exits.
        while (true){
            
            // This will receive the new connection.
            tcp::socket socket{ioc};
            
            // Block until we get a connection.
            acceptor.accept(socket);
            
            // Create new connection and add to storage.
            m_pImpl->userConnections.push_back(
                std::make_unique<UserConnection>(
                    std::move(socket)));
        }
    }
}