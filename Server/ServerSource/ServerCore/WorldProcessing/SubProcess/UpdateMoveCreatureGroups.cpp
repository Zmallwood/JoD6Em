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
    
    namespace {
        
        const int k_maxCreatureGroupRadius = 4;
    }
    
    void UpdateMoveCreatureGroups() {
        
        auto worldArea = _<World>().GetCurrWorldArea();
        
        auto &creatureGroups = worldArea->m_creatureGroups;
        
        // Loop over all creature groups.
        for (auto &creatureGroup : creatureGroups) {
            
            // Get the deltas to where the group is moving.
            
            auto dx = creatureGroup.m_destCoord.x -
                      creatureGroup.m_coord.x;
            
            auto dy = creatureGroup.m_destCoord.y -
                      creatureGroup.m_coord.y;
            
            // If group is already at its destination, generate a new destination.
            
            if (dx == 0 && dy == 0) {
                
                creatureGroup.m_destCoord = {rand() % 100, rand() % 100};
            }
            
            auto absDx = std::abs(dx);
            auto absDy = std::abs(dy);
            
            auto normX = 0;
            auto normY = 0;
            
            // Only calculate normalizes deltas if deltas it not zero (causes div. by zero).
            
            if (dx) {
                
                normX = dx/absDx;
            }
            
            if (dy) {
                
                normY = dy/absDy;
            }
            
            // Add the normalized deltas to current coordinate.
            
            creatureGroup.m_coord.x += normX;
            creatureGroup.m_coord.y += normY;
            
            // Loop over all creatures in group.
            
            for (auto creature : creatureGroup.m_creatures) {
                
                auto pos = worldArea->GetCreatureCoord(creature);
                
                if (pos.has_value()) {
                    
                    auto dx = creatureGroup.m_coord.x - pos.value().x;
                    auto dy = creatureGroup.m_coord.y - pos.value().y;
                    
                    // If creatures is outside group radius...
                    if (dx*dx + dy*dy >
                        k_maxCreatureGroupRadius*
                        k_maxCreatureGroupRadius){
                        
                        // Randomly generate move delta values for the craeture.
                        
                        dx += rand() % k_maxCreatureGroupRadius
                              - rand() % k_maxCreatureGroupRadius;
                        
                        dy += rand() % k_maxCreatureGroupRadius
                              - rand() % k_maxCreatureGroupRadius;
                        
                        auto absDx = std::abs(dx);
                        auto absDy = std::abs(dy);
                        
                        auto normX = 0;
                        auto normY = 0;
                        
                        // Calculate normalized deltas only if no risk for div. by zero.
                        
                        if (dx) {
                            
                            normX = dx/absDx;
                        }
                        
                        if (dy) {
                            
                            normY = dy/absDy;
                        }
                        
                        // Calculate new coordinate for creature.
                        
                        auto newX = pos.value().x + normX;
                        auto newY = pos.value().y + normY;
                        
                        // Obtain the tile at this coordinate.
                        
                        auto newTile = worldArea->GetTile(newX, newY);
                        
                        // If tile is valid and not already contains a creature...
                        
                        if (newTile && newTile->GetCreature() == nullptr) {
                            
                            // Move the creature here.
                            
                            newTile->SetCreature(creature);
                            
                            // Remove creature from old tile.
                            
                            worldArea->GetTile(pos.value())->SetCreature(
                                nullptr);
                            
                            // Remove old creature coordinate from world area storage.
                            
                            worldArea->RemoveCreaturePosition(
                                creature);
                            
                            // Add new creature coordinate to world area storage.
                            
                            worldArea->RegisterCreaturePosition(
                                creature, {newX, newY});
                        }
                    }
                }
            }
        }
    }
}