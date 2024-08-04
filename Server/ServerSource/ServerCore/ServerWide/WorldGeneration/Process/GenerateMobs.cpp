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
        auto num_blue_slime_groups = 6;
        auto num_yellow_slime_groups = 6;
        auto num_red_slime_groups = 6;
        
        auto num_mobs_in_group = 6;
        
        
        for (auto i = 0; i < num_blue_slime_groups; i++) {
            auto x_center = rand() % 50 + 50;
            auto y_center = rand() % 50;
            for (auto j = 0; j < num_mobs_in_group; j++) {
                auto x = x_center + rand() % 5 - rand() % 5;
                auto y = y_center + rand() % 5 - rand() % 5;
                
                if (x <  0 || y <0 || x>= 100 || y >= 100)continue;
                
                worldArea->m_tiles[x][y]->m_mob =
                    std::make_shared<Mob>("MobBlueSlime", 1);
            }
        }
        
        for (auto i = 0; i < num_yellow_slime_groups; i++) {
            auto x_center = rand() % 50 + 50;
            auto y_center = rand() % 50 + 50;
            for (auto j = 0; j < num_mobs_in_group; j++) {
                auto x = x_center + rand() % 5 - rand() % 5;
                auto y = y_center + rand() % 5 - rand() % 5;
                if (x <  0 || y <0 || x>= 100 || y >= 100)continue;
                
                worldArea->m_tiles[x][y]->m_mob =
                    std::make_shared<Mob>("MobYellowSlime", 2);
            }
        }
        
        for (auto i = 0; i < num_red_slime_groups; i++){
            auto x_center = rand() % 50;
            auto y_center = rand() % 50 + 50;
            for (auto j = 0; j < num_mobs_in_group; j++) {
                auto x = x_center + rand() % 5 - rand() % 5;
                auto y = y_center + rand() % 5 - rand() % 5;
                if (x <  0 || y <0 || x>= 100 || y >= 100)continue;
                
                worldArea->m_tiles[x][y]->m_mob =
                    std::make_shared<Mob>("MobRedSlime", 3);
            }
        }
    }
}