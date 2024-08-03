/*
 * TileHovering.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class user_connection;
    
    class tile_hovering {
    public:
        tile_hovering(user_connection &user_connection);
        
        void update();
        
        point m_hovered_coordinate = {-1, -1};
        
    private:
        user_connection &m_user_connection;
    };
}