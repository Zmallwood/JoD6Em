/*
 * Cursor.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserConnection;
    
    class Cursor {
    public:
        Cursor(UserConnection& userConnection);
        
        void Render(WebSocket& ws) const;
        
    private:
        UserConnection& m_userConnection;
        
        const std::string k_cursorImageName = "CursorDefault"; ///< Image name for default cursor style.

        const float k_cursorSize = 0.03f; ///< Size of rendered cursor symbol.
    };
}