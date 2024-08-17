/*
 * Cursor.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "CursorTypes.hpp"
#include "ServerCore/UserGameInstance/Cursor/CursorTypes.hpp"

namespace JoD {

///
/// Custom cursor object which replaces the default system cursor.
///
class Cursor {
    
  public:
    
    ///
    /// Render the cursor to canvas.
    ///
    /// @param webSocket Users web socket object.
    ///
    void Render(UserID userID) const;
    
    ///
    /// Reset cursor type to default type at start of each frame.
    ///
    void ResetCursorType();
    
    ///
    /// Set the current cursor type to new value.
    ///
    /// @param newCursorType New cursor type.
    ///
    void SetCursorType(CursorTypes newCursorType) {
        
        m_currCursorType = newCursorType;
    }
    
  private:
    
    // Members
    
    CursorTypes m_currCursorType {CursorTypes::Default};              ///< Current cursor type, determines image to draw.
    
    const std::map<CursorTypes, std::string> k_cursorImageNames {     ///< Mapping of cursor images to cursor types.
        {CursorTypes::Default, "CursorDefault"},
        {CursorTypes::Hovering, "CursorHovering"}
    };
    
    const float k_cursorSize {0.045f};                                ///< Size of rendered cursor symbol.
};

}
