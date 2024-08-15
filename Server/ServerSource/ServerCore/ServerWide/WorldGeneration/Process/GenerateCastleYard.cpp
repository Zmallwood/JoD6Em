/*
 * GenerateCastleYard.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateCastleYard.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    void GenerateCastleYard(WorldArea* worldArea) {
        
        for (auto y = 0; y < 25; y++) {
            
            for (auto x = 0; x < 25; x++) {
                
                auto tile = worldArea->GetTile(x, y);
                
                tile->SetGround("GroundCobbleStone");
            }
        }
    }
}