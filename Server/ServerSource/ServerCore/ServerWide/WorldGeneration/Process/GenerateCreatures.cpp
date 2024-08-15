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
        
        struct CreatureGenerateArgs {
            
            WorldArea* worldArea;
            std::string creatureName;
            int numGroups;
            int numCreaturesInGroup;
            Box area;
            int creatureLevel;
        };
        
        void GenerateCreatureGroupOfType(CreatureGenerateArgs args);
    }
    
    void GenerateCreatures(WorldArea* worldArea) {
        
        GenerateCreatureGroupOfType(
            {.worldArea = worldArea, .creatureName="CreatureBlueSlime",
             .numGroups = 6, .numCreaturesInGroup = 6,
             .area = {50, 0, 50, 50}, .creatureLevel=1});
        
        GenerateCreatureGroupOfType(
            {.worldArea = worldArea, .creatureName="CreatureYellowSlime",
             .numGroups = 6, .numCreaturesInGroup = 6,
             .area = {50, 50, 50, 50}, .creatureLevel=2});
        
        GenerateCreatureGroupOfType(
            {.worldArea = worldArea, .creatureName="CreatureRedSlime",
             .numGroups = 6, .numCreaturesInGroup = 6,
             .area = {0, 50, 50, 50}, .creatureLevel=3});
        
        GenerateCreatureGroupOfType(
            {.worldArea = worldArea, .creatureName="CreatureCow",
             .numGroups = 6, .numCreaturesInGroup = 6,
             .area = {0, 0, 100, 100}, .creatureLevel=3});
    }
    
    namespace {
        
        void GenerateCreatureGroupOfType(CreatureGenerateArgs args) {
            
            for (auto i = 0; i < args.numGroups; i++) {
                
                const auto xCenter = rand() % args.area.w + args.area.x;
                const auto yCenter = rand() % args.area.h + args.area.y;
                
                CreatureGroup creatureGroup;
                
                creatureGroup.m_coord = {xCenter, yCenter};
                
                for (auto j = 0; j < args.numCreaturesInGroup; j++) {
                    
                    const auto x = xCenter + rand() % 5 - rand() % 5;
                    const auto y = yCenter + rand() % 5 - rand() % 5;
                    
                    if (!args.worldArea->IsValidCoord({x,y})) {
                        
                        continue;
                    }
                    
                    if (args.worldArea->GetTile(x, y)->GetCreature()) {
                        
                        continue;
                    }
                    
                    if (args.worldArea->GetTile(
                            x,
                            y)->GetGround() ==
                        Hash("GroundWater")) {
                        
                        continue;
                    }
                    
                    const auto newCreature =
                        std::make_shared<Creature>(
                            args.creatureName,
                            args.creatureLevel);
                    
                    creatureGroup.m_creatures.push_back(newCreature);
                    
                    args.worldArea->RegisterCreaturePosition(
                        newCreature,
                        {x, y});
                    
                    args.worldArea->GetTile(x, y)->SetCreature(newCreature);
                }
                
                args.worldArea->m_creatureGroups.push_back(creatureGroup);
            }
        }
    }
}