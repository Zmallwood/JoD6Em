/*
 * ClearWithGrass.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClearWithGrass.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    void ClearWithGrass(std::shared_ptr<WorldArea> worldArea) {
        
        for (auto y = 0; y < _<GameProperties>().k_worldAreaSize.h; y++) {
            
            for (auto x = 0; x < _<GameProperties>().k_worldAreaSize.w; x++) {
                
                worldArea->m_tiles[x][y]->m_ground = Hash("GroundGrass");
            }
        }
    }
}