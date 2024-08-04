/*
 * MainScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MainScene.h"
#include "ServerCore/Net/UserConnection.h"
#include "Process/TileHovering.h"
#include "Process/MouseMovement.h"
#include "Process/MobTargeting.h"
#include "MainSceneMath/TileGridMath.h"
#include "Configuration/GameProperties.h"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.h"
#include "ServerCore/ServerWide/WorldStructure/World.h"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.h"
#include "ServerCore/ServerWide/WorldStructure/Tile.h"
#include "ServerCore/ServerWide/WorldStructure/Mob.h"

namespace JoD {
    void MainScene::UpdateDerived() {
        m_user_connection.m_tile_hovering->Update();
        m_user_connection.m_mouse_movement->Update();
        m_user_connection.m_mob_targeting->Update();
    }
    
    void MainScene::RenderDerived(WebSocket &
                                  webSocket) {
        auto tile_size =
            CalculateTileSize(m_user_connection.GetAspectRatio());
        auto player_coordinate =
            m_user_connection.m_player->m_coordinate;
        auto num_grid_rows = _<GameProperties>().k_num_grid_rows;
        auto num_grid_cols = CalculateNumGridCols(m_user_connection.GetAspectRatio());
        auto smallValue = 0.0001f;
        for (auto y = 0; y < num_grid_rows; y++){
            for (auto x = 0; x < num_grid_cols; x++){
                auto coord_x = player_coordinate.x -
                               (num_grid_cols - 1) / 2 + x;
                auto coord_y = player_coordinate.y -
                               (num_grid_rows - 1) / 2 + y;
                if (coord_x < 0 || coord_y < 0 || coord_x >= 100 ||
                    coord_y >= 100) continue;
                auto tile =
                    _<World>().m_current_world_area->m_tiles[coord_x][
                        coord_y];
                auto ground = tile->m_ground;
                if (ground == Hash("GroundWater")) {
                    auto animIndex = ((std::chrono::high_resolution_clock::now().time_since_epoch().count()/1000000)%1200)/400;
                    ground = Hash("GroundWater_" + std::to_string(animIndex));
                }
                m_user_connection.SendImageDrawInstruction(
                    webSocket,
                    ground,
                    {x * tile_size.w, y * tile_size.h,
                     tile_size.w + smallValue,
                     tile_size.h + smallValue});
                if (coord_x ==
                    m_user_connection.m_tile_hovering->
                    m_hovered_coordinate.x &&
                    coord_y ==
                    m_user_connection.m_tile_hovering->
                    m_hovered_coordinate.y){
                    m_user_connection.SendImageDrawInstruction(
                        webSocket,
                        "HoveredTile",
                        {x * tile_size.w, y * tile_size.h, tile_size.w,
                         tile_size.h});
                }
                if (tile->m_object) {
                    m_user_connection.SendImageDrawInstruction(
                        webSocket,
                        tile->m_object,
                        {x * tile_size.w, y * tile_size.h, tile_size.w,
                         tile_size.h});
                }
                if (tile->m_mob) {
                    if (tile->m_mob ==
                        m_user_connection.m_mob_targeting->
                        m_targeted_creature){
                        m_user_connection.SendImageDrawInstruction(
                            webSocket,
                            "TargetedMob",
                            {x * tile_size.w, y * tile_size.h,
                             tile_size.w,
                             tile_size.h});
                    }
                    m_user_connection.SendImageDrawInstruction(
                        webSocket,
                        tile->m_mob->m_type,
                        {x * tile_size.w, y * tile_size.h, tile_size.w,
                         tile_size.h});
                    m_user_connection.SendTextDrawInstruction(
                        webSocket,
                        "Mob, Lvl." +
                        std::to_string(tile->m_mob->m_level),
                        {x*tile_size.w, (y - 0.5f)*tile_size.h});
                }
                if (coord_x == player_coordinate.x &&
                    coord_y == player_coordinate.y){
                    m_user_connection.SendImageDrawInstruction(
                        webSocket, "Player", {
                        x * tile_size.w, y * tile_size.h,
                        tile_size.w,
                        tile_size.h});
                }
            }
        }
    }
}