/*
 * WSServerConnection.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
/// Connects to to web socket server and enables sending messages over the connection
/// after it has opened.
class WSServerConnection {
  public:
    /// Open the connection to the web socket server.
    void Connect() const;
    
    /// Send message to the server.
    /// @param messageType Message type to be sent.
    void SendMessage(int messageType) const;
    
    ///  Send message to the server.
    /// @param data Int array data to send.
    /// @param length Length of the int array data.
    void SendMessage(const int *data, int length) const;
    
    /// Set the WebSocketEvent object associated with the connection to the game server.
    /// @param value The new WebSocketEvent object.
    void SetWebSocketEvent(
        std::unique_ptr<const EmscriptenWebSocketOpenEvent> value) {
        m_webSocketEvent = std::move(value);
    }
    
  private:
// Web socket event object related to the opened connection.
    std::unique_ptr<const EmscriptenWebSocketOpenEvent>
    m_webSocketEvent;
// Host name of the server to connect to.
    //const std::string k_host {"164.90.238.23"};
// Host name of the server to connect to.
    const std::string k_host {"localhost"};
// Port number to open the connection at.
    const int k_port {8765};
};
}
