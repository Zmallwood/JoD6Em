/*
 * Cursor.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Cursor.hpp"
#include "ServerCore/Net/UserConnection.hpp"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace JoD {
    
    Cursor::Cursor(UserConnection& userConnection)
        : m_userConnection(userConnection) {
        
    }
    
    void Cursor::Render(WebSocket& ws) const {
        
        auto mousePosition = m_userConnection.m_mousePosition; // Get current mouse position.
        // Obtain cursor dimensions.
        auto cursorWidth = k_cursorSize;
        auto cursorHeight = k_cursorSize*m_userConnection.GetAspectRatio();
        // Calculate cursor position.
        auto cursorX = mousePosition.x - cursorWidth / 2;
        auto cursorY = mousePosition.y - cursorHeight / 2;
        // Create render destination rectangle.
        auto cursorDestination = RectF{
            cursorX, cursorY, cursorWidth,
            cursorHeight};
        // Render the cursor image.
        m_userConnection.SendImageDrawInstruction(
            ws, k_cursorImageName,
            cursorDestination);
    }
}