/*
 * GenerateCreatures.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateCreatures.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Creature.hpp"

namespace JoD {
    
    namespace {
        
        void GenerateCreatureGroupOfType(
            WorldArea *worldArea,
            std::string_view creatureName,
            int numGroups, int numCreaturesInGroup, Box area, int level);
    }
    
    void GenerateCreatures(WorldArea* worldArea) {
        
        GenerateCreatureGroupOfType(
            worldArea, "CreatureBlueSlime", 6, 6,
            {50, 0, 50, 50}, 1);
        GenerateCreatureGroupOfType(
            worldArea, "CreatureYellowSlime", 6, 6,
            {50, 50, 50, 50}, 2);
        GenerateCreatureGroupOfType(
            worldArea, "CreatureRedSlime", 6, 6,
            {0, 50, 50, 50}, 3);
        GenerateCreatureGroupOfType(
            worldArea, "CreatureCow", 60, 6,
            {0, 0, 100, 100}, 3);
    }
    
    namespace {
        
        void GenerateCreatureGroupOfType(
            WorldArea *worldArea,
            std::string_view creatureName,
            int numGroups, int numCreaturesInGroup, Box area, int level) {
            
            for (auto i = 0; i < numGroups; i++) {
                
                const auto xCenter = rand() % area.w + area.x;
                const auto yCenter = rand() % area.h + area.y;
                
                CreatureGroup creatureGroup;
                
                creatureGroup.m_coord = {xCenter, yCenter};
                
                for (auto j = 0; j < numCreaturesInGroup; j++) {
                    
                    const auto x = xCenter + rand() % 5 - rand() % 5;
                    const auto y = yCenter + rand() % 5 - rand() % 5;
                    
                    if (!worldArea->IsValidCoord({x,y})) {
                        
                        continue;
                    }
                    
                    if (worldArea->GetTile(x, y)->GetCreature()) {
                        
                        continue;
                    }
                    
                    if (worldArea->GetTile(
                            x,
                            y)->GetGround() ==
                        Hash("GroundWater")) {
                        
                        continue;
                    }
                    
                    const auto newCreature =
                        std::make_shared<Creature>(creatureName, level);
                    
                    creatureGroup.m_creatures.push_back(newCreature);
                    
                    worldArea->RegisterCreaturePosition(newCreature, {x, y});
                    
                    worldArea->GetTile(x, y)->SetCreature(newCreature);
                }
                
                worldArea->m_creatureGroups.push_back(creatureGroup);
            }
        }
    }
}