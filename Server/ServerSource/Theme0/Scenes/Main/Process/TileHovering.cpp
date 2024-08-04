/*
 * TileHovering.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TileHovering.hpp"
#include "Theme0/Scenes/Main/MainSceneMath/TileGridMath.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "Configuration/GameProperties.hpp"
#include "ServerCore/Net/UserConnection.hpp"

namespace JoD {
    TileHovering::TileHovering(
        UserConnection &user_connection) : m_user_connection(user_connection){
    }
    
    void
    TileHovering::Update(){
        auto tile_size =
            CalculateTileSize(m_user_connection.GetAspectRatio());
        auto player_coordinate = m_user_connection.m_player->m_coordinate;
        auto num_rows = _<GameProperties>().k_num_grid_rows;
        auto num_cols = CalculateNumGridCols(m_user_connection.GetAspectRatio());
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