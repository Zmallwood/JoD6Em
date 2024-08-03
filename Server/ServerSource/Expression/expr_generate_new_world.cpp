/*
 * expr_generate_new_world.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_generate_new_world.h"
#include "expr_world_generation_clear_with_grass.h"
#include "expr_world_generation_generate_water.h"
#include "ServerCore/WorldStructure/world.h"
#include "ServerCore/WorldStructure/world_area.h"
#include "ServerCore/WorldStructure/tile.h"
#include "ServerCore/WorldStructure/creature.h"

namespace jod {
    expr_return_struct expr_generate_new_world::eval() {
        expr_world_generation_clear_with_grass().eval();
        expr_world_generation_generate_water().eval();

        auto world_area = _<world>().m_current_world_area;

        auto num_object_tree1s = 300;

        for (auto i = 0; i < num_object_tree1s; i++) {
            auto x = rand() % 100;
            auto y = rand() % 100;

            if (world_area->m_tiles[x][y]->m_ground != jod::hash("GroundWater")) {
                world_area->m_tiles[x][y]->m_object = jod::hash("ObjectTree1");
            }
        }

        auto road_x = 0;
        auto road_y = 0;

        for (auto i = 0; i < 25; i++) {
            world_area->m_tiles[road_x][road_y]->m_ground = jod::hash("GroundCobbleStone");
            road_x++;
            road_y++;
        }

        for (auto i = 0; i < 50; i++) {
            world_area->m_tiles[road_x][road_y]->m_ground = jod::hash("GroundCobbleStone");
            road_x++;
        }

        for (auto i = 0; i < 50; i++) {
            world_area->m_tiles[road_x][road_y]->m_ground = jod::hash("GroundCobbleStone");
            road_y++;
        }

        for (auto i = 0; i < 50; i++) {
            world_area->m_tiles[road_x][road_y]->m_ground = jod::hash("GroundCobbleStone");
            road_x--;
        }

        for (auto i = 0; i < 25; i++) {
            world_area->m_tiles[road_x][road_y]->m_ground = jod::hash("GroundCobbleStone");
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

                world_area->m_tiles[x][y]->m_creature = std::make_shared<creature>("MobBlueSlime", 1);
            }
        }

        for (auto i = 0; i < num_yellow_slime_groups; i++) {
            auto x_center = rand() % 50 + 50;
            auto y_center = rand() % 50 + 50;
            for (auto j = 0; j < num_mobs_in_group; j++) {
                auto x = x_center + rand() % 5 - rand() % 5;
                auto y = y_center + rand() % 5 - rand() % 5;
                if (x <  0 || y <0 || x>= 100 || y >= 100)continue;

                world_area->m_tiles[x][y]->m_creature = std::make_shared<creature>("MobYellowSlime", 2);
            }
        }

        for (auto i = 0; i < num_red_slime_groups; i++) {
            auto x_center = rand() % 50;
            auto y_center = rand() % 50 + 50;
            for (auto j = 0; j < num_mobs_in_group; j++) {
                auto x = x_center + rand() % 5 - rand() % 5;
                auto y = y_center + rand() % 5 - rand() % 5;
                if (x <  0 || y <0 || x>= 100 || y >= 100)continue;

                world_area->m_tiles[x][y]->m_creature = std::make_shared<creature>("MobRedSlime", 3);
            }
        }

        return {0};
        // return {expr_world_generation_clear_with_grass().eval().return_code
        //         ||
        //         expr_world_generation_generate_water().eval().return_code};
    }
}