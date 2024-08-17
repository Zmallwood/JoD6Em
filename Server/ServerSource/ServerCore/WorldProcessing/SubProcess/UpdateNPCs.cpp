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
        
        if (npc) {
            
            if (npc->GetIsFollowingPath()) {
                
                if (Now() >
                    npc->GetTimeLastMove() +
                    Duration(
                        Millis(
                            static_cast<int>(1000/
                                             npc
                                             ->
                                             GetMovementSpeed())))){
                    
                    auto reversePath = wArea->m_roadPath;
                    
                    std::reverse(reversePath.begin(), reversePath.end());
                    
                    for (auto it = reversePath.begin();
                         it != reversePath.end(); it++) {
                        
                        if (it->x == coord.x && it->y == coord.y) {
                            
                            it++;
                            
                            if (it == reversePath.end()) {
                                
                                auto beginningTile =
                                    wArea->GetTile(reversePath[0]);
                                
                                beginningTile->SetNPC(npc);
                                
                                wArea->GetTile(
                                    coord.x,
                                    coord.y)->SetNPC(
                                    nullptr);
                                
                                break;
                            }
                            
                            auto newTile = wArea->GetTile(it->x, it->y);
                            
                            if (newTile && newTile->GetNPC() == nullptr) {
                                
                                newTile->SetNPC(npc);
                                
                                wArea->GetTile(
                                    coord.x,
                                    coord.y)->SetNPC(
                                    nullptr);
                            }
                        }
                    }
                    
                    npc->SetTimeLastMove(Now());
                }
            }
        }
    }
}