/*
 * GenerateNPCs.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateNPCs.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "NPC.hpp"
#include "Configuration/GameProperties.hpp"
#include <memory>

namespace JoD {
    
    void GenerateNPCs(WorldArea* worldArea) {
        
        auto tileStep = 0;
        auto tileStepOffset = 12;
        auto npcCreationInterval = 18;
        
        for (auto y = 0; y < _<GameProperties>().GetWorldAreaSize().h; y++) {
            
            for (auto x = 0; x < _<GameProperties>().GetWorldAreaSize().w;
                 x++){
                
                auto tile = worldArea->GetTile(x,y);
                
                // Check if current tile is of road type.
                if (tile->GetGround() == Hash("GroundSlabs")
                    || tile->GetGround() == Hash("GroundTrail")
                    || tile->GetGround() == Hash("Bridge")) {
                    
                    // Only create horse with an interval equal to horseCreationInterval.
                    if (tileStep % npcCreationInterval ==
                        tileStepOffset) {
                        
                        auto newNPC = std::make_unique<NPC>();
                        newNPC->SetIsFollowingPath(true);
                        
                        tile->SetNPC(std::move(newNPC));
                    }
                    
                    tileStep++;
                }
            }
        }
    }
}