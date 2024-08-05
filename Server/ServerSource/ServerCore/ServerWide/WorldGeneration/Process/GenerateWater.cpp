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
        
        auto numLakes = 15;
        
        for (auto i = 0; i < numLakes; i++){
            
            auto xCenter = rand() % 100;
            auto yCenter = rand() % 100;
            
            auto r = 3 + rand() % 11;
            
            for (auto y = yCenter - r; y <= yCenter + r; y++){
                
                for (auto x = xCenter - r; x <= xCenter + r; x++){
                    
                    if (x < 0 || y < 0 || x >= 100 || y >= 100) {
                        
                        continue;
                    }
                    
                    auto dx = x - xCenter;
                    auto dy = y - yCenter;
                    
                    if (dx * dx + dy * dy <= r * r) {
                        
                        worldArea->m_tiles[x][y]->m_ground =
                            Hash("GroundWater");
                    }
                }
            }
        }
    }
}