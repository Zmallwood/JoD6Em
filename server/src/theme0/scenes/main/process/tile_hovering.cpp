// tile_hovering.cpp
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
//

#include "tile_hovering.h"
#include "theme0/scenes/main/main_scene_math/tile_grid_math.h"
#include "server_core/core_game_objects/player.h"
#include "configuration/game_properties.h"
#include "server_core/net/user_connection.h"

namespace jod {
    tile_hovering::tile_hovering(user_connection &user_connection) : m_user_connection(user_connection){
    }
    
    void
    tile_hovering::update(){
        auto tileSize = calc_tile_size(m_user_connection.get_aspect_ratio());
        auto playerCoord = m_user_connection.m_player->m_coord;
        auto numRows = _<game_properties>().numGridRows;
        auto numCols = numRows;
        auto tileX =
            playerCoord.x - (numCols - 1) / 2 +
            static_cast<int>(m_user_connection.m_mousePosition.x / tileSize.w);
        auto tileY =
            playerCoord.y - (numRows - 1) / 2 +
            static_cast<int>(m_user_connection.m_mousePosition.y / tileSize.h);
        m_hoveredCoordinate = {tileX, tileY};
    }
}