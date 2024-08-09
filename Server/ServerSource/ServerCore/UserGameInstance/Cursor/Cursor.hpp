/*
 * Cursor.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class EngineInstance;
    
    ///
    /// Custom cursor object which replaces the default system cursor.
    ///
    class Cursor {
        
      public:
        ///
        /// Construct a new Cursor object by forwarding an user connection reference.
        /// 
        /// @param userConnection User connection object for current user.
        ///
        Cursor(const EngineInstance& engineInstance);
        
        ///
        /// Render the cursor to canvas.
        /// 
        /// @param webSocket Users web socket object.
        ///
        void Render(UserID userID, WebSocket& webSocket) const;
        
      private:
        const EngineInstance& m_engineInstance; ///< User connection object for associated user.
        const std::string k_cursorImageName {"CursorDefault"}; ///< Image name for default cursor style.
        const float k_cursorSize {0.03f}; ///< Size of rendered cursor symbol.
    };
}