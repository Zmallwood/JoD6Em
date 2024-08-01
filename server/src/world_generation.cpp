// Copyright (c) 2024 Andreas Åkerberg.

#include "world_generation.h"
#include "world.h"

namespace jod {
    void
    generate_new_world(){
        auto worldArea = _<world>().m_currentWorldArea;
        for (auto y = 0; y < 100; y++)
            for (auto x = 0; x < 100; x++)
                worldArea->m_tiles[x][y]->m_ground = jod::hash("GroundGrass");
        auto numLakes = 15;
        for (auto i = 0; i < numLakes; i++){
            auto xCenter = rand() % 100;
            auto yCenter = rand() % 100;
            auto r = 3 + rand() % 11;
            for (auto y = yCenter - r; y <= yCenter + r; y++){
                for (auto x = xCenter - r; x <= xCenter + r; x++){
                    if (x < 0 || y < 0 || x >= 100 || y >= 100) continue;
                    auto dx = x - xCenter;
                    auto dy = y - yCenter;
                    if (dx * dx + dy * dy <= r * r)
                        worldArea->m_tiles[x][y]->m_ground =
                            jod::hash("GroundWater");
                }
            }
        }
    }
}