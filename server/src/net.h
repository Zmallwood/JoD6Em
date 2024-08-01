// net.h
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
///////////////////////////////////////////////////////////

#pragma once

namespace jod {
    class client;
    
    class web_socket_server {
    public:
        void start(std::string socketAddress, std::string socketPort);
        
    private:
        std::vector<std::shared_ptr<client> > m_clients;
    };
}