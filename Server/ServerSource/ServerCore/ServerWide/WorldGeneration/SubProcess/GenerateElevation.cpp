/*
 * GenerateElevation.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateElevation.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"

namespace JoD {

void GenerateElevation(WorldArea* worldArea) {
    
// In parameter, number of hills to generate.
    auto numHills = 20;
    
    for (auto i = 0; i < numHills; i++) {
        
// Set properties for each hill.
        auto xCenter = rand() % worldArea->GetSize().w;
        auto yCenter = rand() % worldArea->GetSize().h;
        auto rMax = 3 + rand() % 8;
        
// Loop over the area several times, decrease the radius each time.
        for (auto r = rMax; r >= 0; r -= 3) {
            
            for (auto y = yCenter - r; y <= yCenter + r; y++) {
                
                for (auto x = xCenter - r; x <= xCenter + r; x++) {
                    
// Coordinate is outside world area, skip iteration.
                    if (!worldArea->IsValidCoord(x, y)) {
                        
                        continue;
                    }
                    
                    auto tile = worldArea->GetTile(x, y);
                    
// Tile is water, skip iteration.
                    if (tile->GetGround() == Hash("GroundWater")) {
                        
                        continue;
                    }
                    
                    auto dx = x - xCenter;
                    auto dy = y - yCenter;
                    
// Compare squared radiuses. If inside the current iterated radius,
// increase elevation by 1.
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