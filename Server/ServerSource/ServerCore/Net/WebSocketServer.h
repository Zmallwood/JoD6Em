/*
 * WebSocketServer.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserConnection;
    
    class WebSocketServer {
    public:
        void Run(std::string socket_address, std::string socket_port);
        
    private:
        std::vector<std::shared_ptr<UserConnection> > m_user_connections;
    };
}