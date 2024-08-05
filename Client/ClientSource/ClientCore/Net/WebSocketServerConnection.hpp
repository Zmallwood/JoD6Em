/*
 * WebSocketServerConnection.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Connects to to web socket server and enables sending messages over the connection
    /// after it has opened.
    ///
    class WebSocketServerConnection {
        
      public:
        ///
        /// Open the connection to the web socket server.
        ///
        void Connect() const;
        
        ///
        /// Send message to the server.
        ///
        /// @param messageType Message type to be sent.
        ///
        void SendMessage(int messageType) const;
        
        std::shared_ptr<const EmscriptenWebSocketOpenEvent>
        m_webSocketEvent; ///< Web socket event object related to the opened connection.
        
      private:
        const std::string k_host {"localhost"}; ///< Host name of the server to connect to.
        
        const int k_port {8765}; ///< Port number to open the connection at.
    };
}