/*
 * expr_world_generation_clear_with_grass.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_world_generation_clear_with_grass.h"
#include "ServerCore/WorldStructure/world.h"
#include "ServerCore/WorldStructure/world_area.h"
#include "ServerCore/WorldStructure/tile.h"

namespace jod {
    expr_return_struct expr_world_generation_clear_with_grass::eval() {
        auto world_area = _<world>().m_current_world_area;
        for (auto y = 0; y < 100; y++)
            for (auto x = 0; x < 100; x++)
                world_area->m_tiles[x][y]->m_ground = jod::hash("GroundGrass");
        return {0};
    }
}