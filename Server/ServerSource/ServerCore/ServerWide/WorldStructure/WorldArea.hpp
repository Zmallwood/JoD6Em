/*
 * WorldArea.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class Tile;
    
    class WorldArea {
      public:
        WorldArea();
        
        std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
    };
}