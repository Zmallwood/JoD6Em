// tile_hovering.h
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
///////////////////////////////////////////////////////////

#pragma once

namespace jod {
    class client;
    
    class tile_hovering {
    public:
        tile_hovering(client &client);
        
        void update();
        
        point m_hoveredCoordinate = {-1, -1};
        
    private:
        client &m_client;
    };
}