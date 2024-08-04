/*
 * Cursor.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserConnection;
    
    class Cursor {
    public:
        Cursor(UserConnection& user_connection);
        
        void Render(WebSocket& ws);
        
    private:
        UserConnection& m_user_connection;
        
        const std::string k_cursor_image_name = "CursorDefault"; ///< Image name for default cursor style.

        const float k_cursor_size = 0.03f; ///< Size of rendered cursor symbol.
    };
}