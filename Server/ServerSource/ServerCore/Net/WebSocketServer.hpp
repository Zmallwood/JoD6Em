/*
 * WebSocketServer.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "UserConnection.hpp"

namespace JoD {
    
    class UserConnection;
    
    ///
    /// Core web socker server object handling all incoming user connections.
    ///
    class WebSocketServer {
        
      public:
        ///
        /// Run web socket server and start listening for incoming connections.
        ///
        /// @param socketAddress Address of the machine hosting the server.
        /// @param socketPort Port number to host the server on.
        ///
        void Run(std::string_view socketAddress, std::string_view socketPort);
        
      private:
        std::vector<std::unique_ptr<UserConnection>>
        m_userConnections; ///< Holds all connected users.
    };
}