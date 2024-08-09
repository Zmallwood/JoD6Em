/*
 * Cursor.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

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
        void Render(UserID userID, WebSocket& webSocket) const;
        
      private:
        const std::string k_cursorImageName {"CursorDefault"}; ///< Image name for default cursor style.
        const float k_cursorSize {0.03f}; ///< Size of rendered cursor symbol.
    };
}