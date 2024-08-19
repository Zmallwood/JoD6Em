/*
 * Cursor.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "CursorTypes.hpp"
#include "ServerCore/UserGameInstance/Cursor/CursorTypes.hpp"

namespace JoD {
/// Custom cursor object which replaces the default system cursor.
class Cursor {
  public:
    /// Render the cursor to canvas.
    /// @param webSocket Users web socket object.
    void Render(UserID userID) const;
    
    /// Reset cursor type to default type at start of each frame.
    void ResetCursorType();
    
    /// Set the current cursor type to new value.
    /// @param newCursorType New cursor type.
    void SetCursorType(CursorTypes newCursorType) {
        m_currCursorType = newCursorType;
    }
    
  private:
// Current cursor type, determines image to draw.
    CursorTypes m_currCursorType {CursorTypes::Default};
// Mapping of cursor images to cursor types.
    const std::map<CursorTypes, std::string> k_cursorImageNames {
        {CursorTypes::Default, "CursorDefault"},
        {CursorTypes::Hovering, "CursorHovering"}
    };
// Size of rendered cursor symbol.
    const float k_cursorSize {0.045f};
};
}
