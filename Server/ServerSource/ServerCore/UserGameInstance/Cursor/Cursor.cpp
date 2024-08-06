/*
 * Cursor.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Cursor.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace JoD {
    
    Cursor::Cursor(UserConnection& userConnection)
        : m_userConnection(userConnection) {
        
    }
    
    void Cursor::Render(WebSocket& webSocket) const {
        
        // Get current mouse position.
        auto mousePosition = m_userConnection.m_userGameInstanceEngine->m_mousePosition;
        
        // Obtain cursor dimensions.
        auto cursorWidth = k_cursorSize;
        auto cursorHeight = k_cursorSize*m_userConnection.m_userGameInstanceEngine->GetAspectRatio();
        
        // Calculate cursor position.
        auto cursorX = mousePosition.x - cursorWidth / 2;
        auto cursorY = mousePosition.y - cursorHeight / 2;
        
        // Create render destination rectangle.
        auto cursorDestination = BoxF{
            cursorX, cursorY, cursorWidth,
            cursorHeight};
        
        // Render the cursor image.
        m_userConnection.SendImageDrawInstruction(
            webSocket, k_cursorImageName,
            cursorDestination);
    }
}