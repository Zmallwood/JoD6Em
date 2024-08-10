/*
 * GenerateMobs.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateMobs.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/Mob.hpp"

namespace JoD {
    
    void GenerateMobs(WorldArea* worldArea) {
        
        const auto numBlueSlimeGroups = 6;
        const auto numYellowSlimeGroups = 6;
        const auto numRedSlimeGroups = 6;
        
        const auto numMobsInGroup = 6;
        
        for (auto i = 0; i < numBlueSlimeGroups; i++) {
            
            const auto xCenter = rand() % 50 + 50;
            const auto yCenter = rand() % 50;
            
            MobGroup mobGroup;
            
            mobGroup.m_coordinate = {xCenter, yCenter};
            
            for (auto j = 0; j < numMobsInGroup; j++) {
                
                const auto x = xCenter + rand() % 5 - rand() % 5;
                const auto y = yCenter + rand() % 5 - rand() % 5;
                
                if (!worldArea->IsValidCoord({x,y})) {
                    
                    continue;
                }
                
                if (worldArea->GetTile(x, y)->GetMob()) {
                    
                    continue;
                }
                
                if (worldArea->GetTile(x, y)->GetGround() == Hash("GroundWater")) {
                    
                    continue;
                }
                
                const auto newMob = std::make_shared<Mob>("MobBlueSlime", 1);
                
                mobGroup.m_mobs.push_back(newMob);
                
                worldArea->RegisterMobPosition(newMob, {x, y});
                
                worldArea->GetTile(x, y)->SetMob(newMob);
            }
            
            worldArea->m_mobGroups.push_back(mobGroup);
        }
        
        for (auto i = 0; i < numYellowSlimeGroups; i++) {
            
            const auto xCenter = rand() % 50 + 50;
            const auto yCenter = rand() % 50 + 50;
            
            MobGroup mobGroup;
            
            mobGroup.m_coordinate = {xCenter, yCenter};
            
            for (auto j = 0; j < numMobsInGroup; j++) {
                
                const auto x = xCenter + rand() % 5 - rand() % 5;
                const auto y = yCenter + rand() % 5 - rand() % 5;
                
                if (!worldArea->IsValidCoord({x,y})) {
                    
                    continue;
                }
                
                if (worldArea->GetTile(x, y)->GetMob()) {
                    
                    continue;
                }
                
                if (worldArea->GetTile(x, y)->GetGround() == Hash("GroundWater")) {
                    
                    continue;
                }
                
                const auto newMob = std::make_shared<Mob>("MobYellowSlime", 2);
                
                worldArea->RegisterMobPosition(newMob, {x, y});
                
                mobGroup.m_mobs.push_back(newMob);
                
                worldArea->GetTile(x, y)->SetMob(newMob);
            }
            
            worldArea->m_mobGroups.push_back(mobGroup);
        }
        
        for (auto i = 0; i < numRedSlimeGroups; i++){
            
            const auto xCenter = rand() % 50;
            const auto yCenter = rand() % 50 + 50;
            
            MobGroup mobGroup;
            
            mobGroup.m_coordinate = {xCenter, yCenter};
            
            for (auto j = 0; j < numMobsInGroup; j++) {
                
                const auto x = xCenter + rand() % 5 - rand() % 5;
                const auto y = yCenter + rand() % 5 - rand() % 5;
                
                if (!worldArea->IsValidCoord({x,y})) {
                    
                    continue;
                }
                
                if (worldArea->GetTile(x, y)->GetMob()) {
                    
                    continue;
                }
                
                if (worldArea->GetTile(x, y)->GetGround() == Hash("GroundWater")) {
                    
                    continue;
                }
                
                const auto newMob = std::make_shared<Mob>("MobRedSlime", 3);
                
                worldArea->RegisterMobPosition(newMob, {x, y});
                
                mobGroup.m_mobs.push_back(newMob);
                
                worldArea->GetTile(x, y)->SetMob(newMob);
            }
            
            worldArea->m_mobGroups.push_back(mobGroup);
        }
        
        auto numCowGroups = 70;
        
        for (auto i = 0; i < numCowGroups; i++){
            
            const auto xCenter = rand() % 100;
            const auto yCenter = rand() % 100;
            
            MobGroup mobGroup;
            
            mobGroup.m_coordinate = {xCenter, yCenter};
            
            for (auto j = 0; j < numMobsInGroup; j++) {
                
                const auto x = xCenter + rand() % 5 - rand() % 5;
                const auto y = yCenter + rand() % 5 - rand() % 5;
                
                if (!worldArea->IsValidCoord({x,y})) {
                    
                    continue;
                }
                
                if (worldArea->GetTile(x, y)->GetMob()) {
                    
                    continue;
                }
                
                if (worldArea->GetTile(x, y)->GetGround() == Hash("GroundWater")) {
                    
                    continue;
                }
                
                const auto newMob = std::make_shared<Mob>("MobCow", 3);
                
                worldArea->RegisterMobPosition(newMob, {x, y});
                
                mobGroup.m_mobs.push_back(newMob);
                
                worldArea->GetTile(x, y)->SetMob(newMob);
            }
            
            worldArea->m_mobGroups.push_back(mobGroup);
        }
    }
}