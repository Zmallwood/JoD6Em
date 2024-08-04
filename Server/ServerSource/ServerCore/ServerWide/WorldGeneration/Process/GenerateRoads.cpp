/*
 * GenerateRoads.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateRoads.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"

namespace JoD {
    void GenerateRoads(std::shared_ptr<WorldArea> worldArea) {
        auto road_x = 0;
        auto road_y = 0;
        
        for (auto i = 0; i < 25; i++) {
            worldArea->m_tiles[road_x][road_y]->m_ground =
                Hash("GroundCobbleStone");
            road_x++;
            road_y++;
        }
        
        for (auto i = 0; i < 50; i++) {
            worldArea->m_tiles[road_x][road_y]->m_ground =
                Hash("GroundCobbleStone");
            road_x++;
        }
        
        for (auto i = 0; i < 50; i++) {
            worldArea->m_tiles[road_x][road_y]->m_ground =
                Hash("GroundCobbleStone");
            road_y++;
        }
        
        for (auto i = 0; i < 50; i++) {
            worldArea->m_tiles[road_x][road_y]->m_ground =
                Hash("GroundCobbleStone");
            road_x--;
        }
        
        for (auto i = 0; i < 25; i++) {
            worldArea->m_tiles[road_x][road_y]->m_ground =
                Hash("GroundCobbleStone");
            road_y++;
        }
    }
}