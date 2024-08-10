/*
 * GenerateRock.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateRock.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    void GenerateRock(WorldArea* worldArea) {
        
        auto numRockAreas = 20;
        
        for (auto i = 0; i < numRockAreas; i++) {
            
            auto xCenter = rand() % _<GameProperties>().GetWorldAreaSize().w; 
            auto yCenter = rand() % _<GameProperties>().GetWorldAreaSize().h; 
            auto r = 3 + rand() % 8;
            
            for (auto y = yCenter - r; y <= yCenter + r; y++) {
             
                for (auto x = xCenter - r; x <= xCenter + r; x++) {
                    
                    if (!worldArea->IsValidCoord(x, y)) {
                        
                        continue;
                    }
                    
                    auto dx = x - xCenter;
                    auto dy = y - yCenter;
                    
                    if (dx*dx + dy*dy <= r*r) {
                        
                        auto tile = worldArea->GetTile(x, y);
                        
                        if (tile->GetElevation() > 2) {
                            
                            tile->SetGround("GroundRock");
                        }
                    }
                }
            }
        }
    }
}