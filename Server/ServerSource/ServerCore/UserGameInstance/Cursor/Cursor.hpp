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
        
        void ResetCursorType();
        
        void SetCursorType(CursorTypes newCursorType) {
            
            m_currCursorType = newCursorType;
        }

      private:

        // Members
        
        CursorTypes m_currCursorType {CursorTypes::Default};
        
        const std::map<CursorTypes, std::string> k_cursorImageNames {
            {CursorTypes::Default, "CursorDefault"},
            {CursorTypes::Hovering, "CursorHovering"}
        };

        const float k_cursorSize {0.045f}; ///< Size of rendered cursor symbol.
    };
}
