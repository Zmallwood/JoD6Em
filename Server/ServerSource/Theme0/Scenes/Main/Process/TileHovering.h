/*
 * TileHovering.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserConnection;
    
    class TileHovering {
    public:
        TileHovering(UserConnection &user_connection);
        
        void Update();
        
        Point m_hovered_coordinate = {-1, -1};
        
    private:
        UserConnection &m_user_connection;
    };
}