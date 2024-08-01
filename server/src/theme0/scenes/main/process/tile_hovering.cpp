// tile_hovering.cpp
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
///////////////////////////////////////////////////////////

#include "tile_hovering.h"
#include "theme0/scenes/main/main_scene_math/tile_grid_math.h"
#include "server_core/core_game_objects/player.h"
#include "configuration/game_properties.h"
#include "client.h"

namespace jod {
    tile_hovering::tile_hovering(client &client) : m_client(client){
    }
    
    void
    tile_hovering::update(){
        auto tileSize = calc_tile_size(m_client.get_aspect_ratio());
        auto playerCoord = m_client.m_player->m_coord;
        auto numRows = _<game_properties>().numGridRows;
        auto numCols = numRows;
        auto tileX =
            playerCoord.x - (numCols - 1) / 2 +
            static_cast<int>(m_client.m_mousePosition.x / tileSize.w);
        auto tileY =
            playerCoord.y - (numRows - 1) / 2 +
            static_cast<int>(m_client.m_mousePosition.y / tileSize.h);
        m_hoveredCoordinate = {tileX, tileY};
    }
}