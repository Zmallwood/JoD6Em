/*
 * web_socket_server.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class user_connection;
    
    class web_socket_server {
    public:
        void start(std::string socketAddress, std::string socketPort);
        
    private:
        std::vector<std::shared_ptr<user_connection> > m_user_connections;
    };
}