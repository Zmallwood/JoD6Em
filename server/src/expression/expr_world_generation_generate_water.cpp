/*
 * expr_world_generation_generate_water.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_world_generation_generate_water.h"
#include "server_core/world_structure/world.h"
#include "server_core/world_structure/world_area.h"
#include "server_core/world_structure/tile.h"

namespace jod {
    expr_return_struct expr_world_generation_generate_water::evaluate() {
        auto world_area = _<world>().m_current_world_area;
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
                            jod::hash("GroundWater");
                }
            }
        }
        return {0};
    }
}