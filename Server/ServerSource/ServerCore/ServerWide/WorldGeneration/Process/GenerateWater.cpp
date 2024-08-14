/*
 * GenerateWater.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateWater.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    void GenerateWater(WorldArea* worldArea) {
        
        const auto numLakes = 15;
        
        for (auto i = 0; i < numLakes; i++){
            
            const auto xCenter = rand() % _<GameProperties>().GetWorldAreaSize().w;
            const auto yCenter = rand() % _<GameProperties>().GetWorldAreaSize().h;
            
            const auto r = 3 + rand() % 11;
            
            for (auto y = yCenter - r; y <= yCenter + r; y++){
                
                for (auto x = xCenter - r; x <= xCenter + r; x++){
                    
                    if (!worldArea->IsValidCoord({x, y})) {
                        
                        continue;
                    }
                    
                    const auto dx = x - xCenter;
                    const auto dy = y - yCenter;
                    
                    if (dx * dx + dy * dy <= r * r) {
                        
                        worldArea->GetTile(x, y)->SetGround(
                            Hash("GroundWater"));
                    }
                }
            }
        }
    }
}