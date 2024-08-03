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
        void run(std::string socket_address, std::string socket_port);
        
    private:
        std::vector<std::shared_ptr<user_connection> > m_user_connections;
    };
}