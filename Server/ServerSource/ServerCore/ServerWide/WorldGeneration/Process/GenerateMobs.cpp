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
    void GenerateMobs(std::shared_ptr<WorldArea> worldArea) {
        auto numBlueSlimeGroups = 6;
        auto numYellowSlimeGroups = 6;
        auto numRedSlimeGroups = 6;
        
        auto numMobsInGroup = 6;
        
        
        for (auto i = 0; i < numBlueSlimeGroups; i++) {
            auto xCenter = rand() % 50 + 50;
            auto yCenter = rand() % 50;
            for (auto j = 0; j < numMobsInGroup; j++) {
                auto x = xCenter + rand() % 5 - rand() % 5;
                auto y = yCenter + rand() % 5 - rand() % 5;
                
                if (x <  0 || y <0 || x>= 100 || y >= 100)continue;
                
                worldArea->m_tiles[x][y]->m_mob =
                    std::make_shared<Mob>("MobBlueSlime", 1);
            }
        }
        
        for (auto i = 0; i < numYellowSlimeGroups; i++) {
            auto xCenter = rand() % 50 + 50;
            auto yCenter = rand() % 50 + 50;
            for (auto j = 0; j < numMobsInGroup; j++) {
                auto x = xCenter + rand() % 5 - rand() % 5;
                auto y = yCenter + rand() % 5 - rand() % 5;
                if (x <  0 || y <0 || x>= 100 || y >= 100)continue;
                
                worldArea->m_tiles[x][y]->m_mob =
                    std::make_shared<Mob>("MobYellowSlime", 2);
            }
        }
        
        for (auto i = 0; i < numRedSlimeGroups; i++){
            auto xCenter = rand() % 50;
            auto yCenter = rand() % 50 + 50;
            for (auto j = 0; j < numMobsInGroup; j++) {
                auto x = xCenter + rand() % 5 - rand() % 5;
                auto y = yCenter + rand() % 5 - rand() % 5;
                if (x <  0 || y <0 || x>= 100 || y >= 100)continue;
                
                worldArea->m_tiles[x][y]->m_mob =
                    std::make_shared<Mob>("MobRedSlime", 3);
            }
        }
    }
}