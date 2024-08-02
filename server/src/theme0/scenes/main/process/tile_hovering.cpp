/*
 * tile_hovering.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "tile_hovering.h"
#include "theme0/scenes/main/main_scene_math/tile_grid_math.h"
#include "server_core/core_game_objects/player.h"
#include "configuration/game_properties.h"
#include "server_core/net/user_connection.h"

namespace jod {
    tile_hovering::tile_hovering(
        user_connection &user_connection) : m_user_connection(user_connection){
    }
    
    void
    tile_hovering::update(){
        auto tile_size =
            calculate_tile_size(m_user_connection.get_aspect_ratio());
        auto player_coordinate = m_user_connection.m_player->m_coordinate;
        auto num_rows = _<game_properties>().k_num_grid_rows;
        auto num_cols = num_rows;
        auto tile_x =
            player_coordinate.x - (num_cols - 1) / 2 +
            static_cast<int>(m_user_connection.m_mouse_position.x /
                             tile_size.w);
        auto tile_y =
            player_coordinate.y - (num_rows - 1) / 2 +
            static_cast<int>(m_user_connection.m_mouse_position.y /
                             tile_size.h);
        m_hovered_coordinate = {tile_x, tile_y};
    }
}