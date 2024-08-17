/*
 * UpdateMoveCreatureGroups.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "UpdateMoveCreatureGroups.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"

namespace JoD {
    
    void UpdateMoveCreatureGroups() {
        
        auto worldArea = _<World>().GetCurrentWorldArea();
        
        auto &creatureGroups = worldArea->m_creatureGroups;
        
        for (auto &creatureGroup : creatureGroups) {
            
            auto dx = creatureGroup.m_destCoord.x -
                      creatureGroup.m_coord.x;
            auto dy = creatureGroup.m_destCoord.y -
                      creatureGroup.m_coord.y;
            
            if (dx == 0 && dy == 0) {
                
                creatureGroup.m_destCoord = {rand() % 100,
                                             rand() % 100};
            }
            
            auto absDx = std::abs(dx);
            auto absDy = std::abs(dy);
            
            auto normX = 0;
            auto normY = 0;
            
            if (dx) {
                
                normX = dx/absDx;
            }
            
            if (dy) {
                
                normY = dy/absDy;
            }
            
            creatureGroup.m_coord.x += normX;
            creatureGroup.m_coord.y += normY;
            
            for (auto creature : creatureGroup.m_creatures) {
                
                auto pos = worldArea->GetCreatureCoord(creature);
                
                if (pos.has_value()) {
                    
                    const int k_maxCreatureGroupRadius = 4;
                    
                    auto dx = creatureGroup.m_coord.x -
                              pos.value().x;
                    auto dy = creatureGroup.m_coord.y -
                              pos.value().y;
                    
                    
                    if (dx*dx + dy*dy >
                        k_maxCreatureGroupRadius*
                        k_maxCreatureGroupRadius){
                        
                        dx +=  +rand() %
                              k_maxCreatureGroupRadius - rand() %
                              k_maxCreatureGroupRadius;
                        
                        dy +=  +rand() %
                              k_maxCreatureGroupRadius - rand() %
                              k_maxCreatureGroupRadius;
                        
                        auto absDx = std::abs(dx);
                        auto absDy = std::abs(dy);
                        
                        auto normX = 0;
                        auto normY = 0;
                        
                        if (dx) {
                            
                            normX = dx/absDx;
                        }
                        
                        if (dy) {
                            
                            normY = dy/absDy;
                        }
                        
                        auto newX = pos.value().x + normX;
                        auto newY = pos.value().y + normY;
                        
                        auto newTile = worldArea->GetTile(
                            newX,
                            newY);
                        
                        if (newTile &&
                            newTile->GetCreature() == nullptr) {
                            
                            newTile->SetCreature(creature);
                            worldArea->GetTile(
                                pos.value())->SetCreature(
                                nullptr);
                            
                            worldArea->RemoveCreaturePosition(
                                creature);
                            worldArea->RegisterCreaturePosition(
                                creature,
                                {newX,
                                 newY});
                        }
                    }
                }
            }
        }
    }
}