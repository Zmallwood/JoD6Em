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
        
        ///
        ///  Send message to the server.
        ///
        /// @param data Int array data to send.
        /// @param length Length of the int array data.
        ///
        void SendMessage(const int *data, int length) const;
        
        void SetWebSocketEvent(std::unique_ptr<const EmscriptenWebSocketOpenEvent> value) {
            
            m_webSocketEvent = std::move(value);
        }
        
      private:
        std::unique_ptr<const EmscriptenWebSocketOpenEvent>
        m_webSocketEvent; ///< Web socket event object related to the opened connection.
        const std::string k_host {"localhost"}; ///< Host name of the server to connect to.
        const int k_port {8765}; ///< Port number to open the connection at.
    };
}