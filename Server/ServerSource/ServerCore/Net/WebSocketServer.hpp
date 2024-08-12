/*
 * WebSocketServer.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Core web socker server object handling all incoming user connections.
    ///
    class WebSocketServer {
        
      public:
        ///
        /// Construct a new Web Socket Server object.
        ///
        WebSocketServer();

        ///
        /// Destroy the Web Socket Server object. Needed by PIMPL idiom.
        ///
        ~WebSocketServer();
        
        ///
        /// Run web socket server and start listening for incoming connections.
        ///
        /// @param socketAddress Address of the machine hosting the server.
        /// @param socketPort Port number to host the server on.
        ///
        void Run(std::string_view socketAddress, std::string_view socketPort);
        
      private:
        ///
        /// PIMPL struct defined in source file.
        ///
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl; ///< PIMPL idiom used for compilation speed reasons.
    };
}