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
    
    void ClearWithGrass(const std::unique_ptr<WorldArea> &worldArea) {
        
        for (auto y = 0; y < _<GameProperties>().GetWorldAreaSize().h; y++) {
            
            for (auto x = 0; x < _<GameProperties>().GetWorldAreaSize().w; x++) {
                
                worldArea->m_tiles[x][y]->SetGround(Hash("GroundGrass"));
            }
        }
    }
}