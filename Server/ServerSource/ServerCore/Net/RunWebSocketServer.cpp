/*
 * RunWebSocketServer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RunWebSocketServer.hpp"
#include "WebSocketServer.hpp"

namespace JoD {
    
    void RunWebSocketServer(
        std::string_view socketAddress,
        std::string_view socketPort) {
        
        // Get WebSocketServer singleton instance and run it.
        _<WebSocketServer>().Run(socketAddress, socketPort);
    }
}