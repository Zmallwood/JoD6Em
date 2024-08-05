/*
 * ClearWithGrass.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClearWithGrass.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"

namespace JoD {
    
    void ClearWithGrass(std::shared_ptr<WorldArea> worldArea) {
        
        for (auto y = 0; y < 100; y++)
            for (auto x = 0; x < 100; x++)
                worldArea->m_tiles[x][y]->m_ground = Hash("GroundGrass");
    }
}