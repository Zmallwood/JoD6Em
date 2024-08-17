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
    
    auto wArea = _<World>().GetCurrWorldArea();
    
    auto npc = tile->GetNPC();
    
    if (npc && npc->GetIsFollowingPath()) {
        
        if (Now() >
            npc->GetTimeLastMove() +
            Duration(Millis(static_cast<int>(1000/npc->GetMS())))){
            
            auto revPath = wArea->m_roadPath;
            
            std::reverse(revPath.begin(), revPath.end());
            
            for (auto it = revPath.begin(); it != revPath.end(); it++) {
                
                if (it->x == coord.x && it->y == coord.y) {
                    
                    it++;
                    
                    if (it == revPath.end()) {
                        
                        auto startTile = wArea->GetTile(revPath[0]);
                        
                        startTile->SetNPC(npc);
                        
                        wArea->GetTile(coord)->SetNPC(nullptr);
                        
                        break;
                    }
                    
                    auto newTile = wArea->GetTile(it->x, it->y);
                    
                    if (newTile && newTile->GetNPC() == nullptr) {
                        
                        newTile->SetNPC(npc);
                        
                        wArea->GetTile(coord)->SetNPC(nullptr);
                    }
                }
            }
            
            npc->SetTimeLastMove(Now());
        }
    }
}

}