/*
 * WorldArea.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class Tile;
    class Mob;
    
    class WorldArea {
        
      public:
        WorldArea();
        
        std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
        std::map<std::shared_ptr<Mob>, Point> m_mobPositions;
    };
}