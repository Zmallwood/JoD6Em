/*
 * UpdateNPCs.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "UpdateNPCs.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "NPC.hpp"

namespace JoD {

void UpdateNPCs(Tile* tile, Point coord) {
    
// Get world area
    
    auto wArea = _<World>().GetCurrWorldArea();
    
// Get NPC object at tile.
    
    auto npc = tile->GetNPC();
    
// Check if NPC is valid and it is following a road path.
    
    if (npc && npc->GetIsFollowingPath()) {
        
// Check if NPC is ready to move.
        
        if (npc->GetTimerMove().Tick(npc->GetMoveSpd())){
            
// Reverse the default road path, making the NPC going in opposite direction.
            
            auto revPath = wArea->m_roadPath;
            
            std::reverse(revPath.begin(), revPath.end());
            
// Loop over points in reverse road path.
            
            for (auto it = revPath.begin(); it != revPath.end(); it++) {
                
// If found tile on path where NPC is located...
                
                if (it->x == coord.x && it->y == coord.y) {
                    
// Iterate to next tile on path.
                    
                    it++;
                    
// If is now on end of path...
                    
                    if (it == revPath.end()) {
                        
// Get the first road point on the path.
                        
                        auto startTile = wArea->GetTile(revPath[0]);
                        
// Move the NPC here.
                        
                        startTile->SetNPC(npc);
                        
// Remove NPC from old tile.
                        
                        wArea->GetTile(coord)->SetNPC(nullptr);
                        
// NPC has moved, can break the loop.
                        
                        break;
                    }
                    
// Get the tile where NPC should move to.
                    
                    auto newTile = wArea->GetTile(it->x, it->y);
                    
// If new tile is valid and dont already contain a NPC...
                    
                    if (newTile && newTile->GetNPC() == nullptr) [[likely]] {
                        
// Move NPC to the new tile.
                        
                        newTile->SetNPC(npc);
                        
// Remove NPC from old tile.
                        
                        wArea->GetTile(coord)->SetNPC(nullptr);
                    }
                }
            }
        }
    }
}

}