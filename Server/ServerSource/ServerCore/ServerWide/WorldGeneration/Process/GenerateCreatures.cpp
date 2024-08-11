/*
 * GenerateCreatures.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateCreatures.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/Creature.hpp"

namespace JoD {
    
    void GenerateCreatures(WorldArea* worldArea) {
        
        const auto numBlueSlimeGroups = 6;
        const auto numYellowSlimeGroups = 6;
        const auto numRedSlimeGroups = 6;
        
        const auto numCreaturesInGroup = 6;
        
        for (auto i = 0; i < numBlueSlimeGroups; i++) {
            
            const auto xCenter = rand() % 50 + 50;
            const auto yCenter = rand() % 50;
            
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
                
                if (worldArea->GetTile(x, y)->GetGround() == Hash("GroundWater")) {
                    
                    continue;
                }
                
                const auto newCreature = std::make_shared<Creature>("MobBlueSlime", 1);
                
                creatureGroup.m_creatures.push_back(newCreature);
                
                worldArea->RegisterMobPosition(newCreature, {x, y});
                
                worldArea->GetTile(x, y)->SetCreature(newCreature);
            }
            
            worldArea->m_creatureGroups.push_back(creatureGroup);
        }
        
        for (auto i = 0; i < numYellowSlimeGroups; i++) {
            
            const auto xCenter = rand() % 50 + 50;
            const auto yCenter = rand() % 50 + 50;
            
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
                
                if (worldArea->GetTile(x, y)->GetGround() == Hash("GroundWater")) {
                    
                    continue;
                }
                
                const auto newCreature = std::make_shared<Creature>("MobYellowSlime", 2);
                
                worldArea->RegisterMobPosition(newCreature, {x, y});
                
                creatureGroup.m_creatures.push_back(newCreature);
                
                worldArea->GetTile(x, y)->SetCreature(newCreature);
            }
            
            worldArea->m_creatureGroups.push_back(creatureGroup);
        }
        
        for (auto i = 0; i < numRedSlimeGroups; i++){
            
            const auto xCenter = rand() % 50;
            const auto yCenter = rand() % 50 + 50;
            
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
                
                if (worldArea->GetTile(x, y)->GetGround() == Hash("GroundWater")) {
                    
                    continue;
                }
                
                const auto newCreature = std::make_shared<Creature>("MobRedSlime", 3);
                
                worldArea->RegisterMobPosition(newCreature, {x, y});
                
                creatureGroup.m_creatures.push_back(newCreature);
                
                worldArea->GetTile(x, y)->SetCreature(newCreature);
            }
            
            worldArea->m_creatureGroups.push_back(creatureGroup);
        }
        
        auto numCowGroups = 70;
        
        for (auto i = 0; i < numCowGroups; i++){
            
            const auto xCenter = rand() % 100;
            const auto yCenter = rand() % 100;
            
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
                
                if (worldArea->GetTile(x, y)->GetGround() == Hash("GroundWater")) {
                    
                    continue;
                }
                
                const auto newCreature = std::make_shared<Creature>("MobCow", 3);
                
                worldArea->RegisterMobPosition(newCreature, {x, y});
                
                creatureGroup.m_creatures.push_back(newCreature);
                
                worldArea->GetTile(x, y)->SetCreature(newCreature);
            }
            
            worldArea->m_creatureGroups.push_back(creatureGroup);
        }
    }
}