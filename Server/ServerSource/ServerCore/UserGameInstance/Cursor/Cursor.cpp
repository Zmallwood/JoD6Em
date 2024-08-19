/*
 * Cursor.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Cursor.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {

void Cursor::Render(UserID userID) const {
    
// Get current mouse position.
    const auto mousePosition =
        _<EngineGet>().GetMousePosition(userID).value();
    
// Obtain cursor dimensions.
    const auto cursorWidth = k_cursorSize;
    const auto cursorHeight = k_cursorSize*
                              _<EngineGet>().GetAspectRatio(userID).value();

// Calculate cursor position.
    const auto cursorX = mousePosition.x - cursorWidth / 2;
    const auto cursorY = mousePosition.y - cursorHeight / 2;
    
// Create render destination rectangle.
    const auto cursorDestination = BoxF{
        cursorX, cursorY, cursorWidth,
        cursorHeight};
    
// Render the cursor image.
    UserSendDrawImage(
        userID, k_cursorImageNames.at(m_currCursorType),
        cursorDestination);
}

void Cursor::ResetCursorType() {
    
// Reset cursor type to default at start of each frame.
    m_currCursorType = CursorTypes::Default;
}

}