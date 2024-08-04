/*
 * WebSocketServer.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserConnection;
    
    class WebSocketServer {
    public:
        void Run(std::string socketAddress, std::string socketPort);
        
    private:
        std::vector<std::shared_ptr<UserConnection> > m_userConnections;
    };
}