/*
 * RunWebSocketServer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RunWSServer.hpp"
#include "WSServer.hpp"

namespace JoD {
    
    void RunWSServer(
        std::string_view socketAddress,
        std::string_view socketPort) {
        
        // Get WebSocketServer singleton instance and run it.
        _<WSServer>().Run(socketAddress, socketPort);
    }
}