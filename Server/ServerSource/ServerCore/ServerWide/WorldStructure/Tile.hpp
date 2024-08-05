/*
 * Tile.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class Mob;
    
    class Tile {
        
      public:
        int m_ground = 0;
        int m_object = 0;
        std::shared_ptr<Mob> m_mob;
    };
}