/*
 * GenerateElevation.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateElevation.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    void GenerateElevation(WorldArea* worldArea) {
        
        auto numHills = 20;
        
        for (auto i = 0; i < numHills; i++) {
            
            auto xCenter = rand() % _<GameProperties>().GetWorldAreaSize().w; 
            auto yCenter = rand() % _<GameProperties>().GetWorldAreaSize().h; 
            auto rMax = 3 + rand() % 8;
            
            for (auto r = rMax; r >= 0; r -= 3) {
                
                for (auto y = yCenter - r; y <= yCenter + r; y++) {
                    
                    for (auto x = xCenter - r; x <= xCenter + r; x++) {
                        
                        if (!worldArea->IsValidCoord(x, y)) {
                            
                            continue;
                        }
                        
                        auto tile = worldArea->GetTile(x, y);
                        
                        if (tile->GetGround() == Hash("GroundWater")) {
                            
                            continue;
                        }
                        
                        auto dx = x - xCenter;
                        auto dy = y - yCenter;
                        
                        if (dx*dx + dy*dy <= r*r) {
                            
                            auto currElevation = tile->GetElevation();
                            currElevation++;
                            tile->SetElevation(currElevation);
                        }
                    }
                }
            }
        }
    }
}