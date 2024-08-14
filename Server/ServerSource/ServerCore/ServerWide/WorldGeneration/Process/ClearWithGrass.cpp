/*
 * ClearWithGrass.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClearWithGrass.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    void ClearWithGrass(WorldArea* worldArea) {
        
        for (auto y = 0; y < _<GameProperties>().GetWorldAreaSize().h; y++) {
            
            for (auto x = 0; x < _<GameProperties>().GetWorldAreaSize().w; x++) {
                
                worldArea->GetTile(x, y)->SetGround(Hash("GroundGrass"));
            }
        }
    }
}