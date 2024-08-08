/*
 * Cursor.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Cursor.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"

namespace JoD {
    
    Cursor::Cursor(const UserGameInstanceEngine& userGameInstanceEngine)
        : m_userGameInstanceEngine(userGameInstanceEngine) {
        
    }
    
    void Cursor::Render(WebSocket& webSocket) const {
        
        // Get current mouse position.
        const auto mousePosition = m_userGameInstanceEngine.m_mousePosition;
        
        // Obtain cursor dimensions.
        const auto cursorWidth = k_cursorSize;
        const auto cursorHeight = k_cursorSize*m_userGameInstanceEngine.GetAspectRatio();
        
        // Calculate cursor position.
        const auto cursorX = mousePosition.x - cursorWidth / 2;
        const auto cursorY = mousePosition.y - cursorHeight / 2;
        
        // Create render destination rectangle.
        const auto cursorDestination = BoxF{
            cursorX, cursorY, cursorWidth,
            cursorHeight};
        
        // Render the cursor image.
        SendImageDrawInstruction(
            webSocket, k_cursorImageName,
            cursorDestination);
    }
}