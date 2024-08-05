/*
 * RunWebSocketServer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RunWebSocketServer.hpp"
#include "WebSocketServer.hpp"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

namespace JoD {
    
    void RunWebSocketServer(
        std::string_view socketAddress,
        std::string_view socketPort) {
        
        _<WebSocketServer>().Run(socketAddress, socketPort);
    }
}