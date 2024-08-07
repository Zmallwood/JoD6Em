/*
 * GenerateWater.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateWater.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"

namespace JoD {
    
    void GenerateWater(std::shared_ptr<WorldArea> worldArea) {
        
        const auto numLakes = 15;
        
        for (auto i = 0; i < numLakes; i++){
            
            const auto xCenter = rand() % 100;
            const auto yCenter = rand() % 100;
            
            const auto r = 3 + rand() % 11;
            
            for (auto y = yCenter - r; y <= yCenter + r; y++){
                
                for (auto x = xCenter - r; x <= xCenter + r; x++){
                    
                    if (x < 0 || y < 0 || x >= 100 || y >= 100) {
                        
                        continue;
                    }
                    
                    const auto dx = x - xCenter;
                    const auto dy = y - yCenter;
                    
                    if (dx * dx + dy * dy <= r * r) {
                        
                        worldArea->m_tiles[x][y]->m_ground =
                            Hash("GroundWater");
                    }
                }
            }
        }
    }
}