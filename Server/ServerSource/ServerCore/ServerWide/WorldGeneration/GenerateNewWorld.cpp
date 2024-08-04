/*
 * GenerateNewWorld.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateNewWorld.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/Mob.hpp"

namespace JoD {
    void GenerateNewWorld() {
        auto world_area = _<World>().m_current_world_area;
        for (auto y = 0; y < 100; y++)
            for (auto x = 0; x < 100; x++)
                world_area->m_tiles[x][y]->m_ground = Hash("GroundGrass");
        auto num_lakes = 15;
        for (auto i = 0; i < num_lakes; i++){
            auto xCenter = rand() % 100;
            auto yCenter = rand() % 100;
            auto r = 3 + rand() % 11;
            for (auto y = yCenter - r; y <= yCenter + r; y++){
                for (auto x = xCenter - r; x <= xCenter + r; x++){
                    if (x < 0 || y < 0 || x >= 100 || y >= 100) continue;
                    auto dx = x - xCenter;
                    auto dy = y - yCenter;
                    if (dx * dx + dy * dy <= r * r)
                        world_area->m_tiles[x][y]->m_ground =
                            Hash("GroundWater");
                }
            }
        }
        
        auto num_object_tree1s = 300;
        
        for (auto i = 0; i < num_object_tree1s; i++) {
            auto x = rand() % 100;
            auto y = rand() % 100;
            
            if (world_area->m_tiles[x][y]->m_ground !=
                Hash("GroundWater")) {
                world_area->m_tiles[x][y]->m_object = Hash("ObjectTree1");
            }
        }
        
        auto road_x = 0;
        auto road_y = 0;
        
        for (auto i = 0; i < 25; i++) {
            world_area->m_tiles[road_x][road_y]->m_ground =
                Hash("GroundCobbleStone");
            road_x++;
            road_y++;
        }
        
        for (auto i = 0; i < 50; i++) {
            world_area->m_tiles[road_x][road_y]->m_ground =
                Hash("GroundCobbleStone");
            road_x++;
        }
        
        for (auto i = 0; i < 50; i++) {
            world_area->m_tiles[road_x][road_y]->m_ground =
                Hash("GroundCobbleStone");
            road_y++;
        }
        
        for (auto i = 0; i < 50; i++) {
            world_area->m_tiles[road_x][road_y]->m_ground =
                Hash("GroundCobbleStone");
            road_x--;
        }
        
        for (auto i = 0; i < 25; i++) {
            world_area->m_tiles[road_x][road_y]->m_ground =
                Hash("GroundCobbleStone");
            road_y++;
        }
        
        
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
                
                world_area->m_tiles[x][y]->m_mob = std::make_shared<Mob>("MobBlueSlime", 1);
            }
        }
        
        for (auto i = 0; i < num_yellow_slime_groups; i++) {
            auto x_center = rand() % 50 + 50;
            auto y_center = rand() % 50 + 50;
            for (auto j = 0; j < num_mobs_in_group; j++) {
                auto x = x_center + rand() % 5 - rand() % 5;
                auto y = y_center + rand() % 5 - rand() % 5;
                if (x <  0 || y <0 || x>= 100 || y >= 100)continue;
                
                world_area->m_tiles[x][y]->m_mob = std::make_shared<Mob>("MobYellowSlime", 2);
            }
        }
        
        for (auto i = 0; i < num_red_slime_groups; i++){
            auto x_center = rand() % 50;
            auto y_center = rand() % 50 + 50;
            for (auto j = 0; j < num_mobs_in_group; j++) {
                auto x = x_center + rand() % 5 - rand() % 5;
                auto y = y_center + rand() % 5 - rand() % 5;
                if (x <  0 || y <0 || x>= 100 || y >= 100)continue;
                
                world_area->m_tiles[x][y]->m_mob = std::make_shared<Mob>("MobRedSlime", 3);
            }
        }
    }
}