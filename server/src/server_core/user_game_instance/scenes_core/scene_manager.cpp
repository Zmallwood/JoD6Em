/*
 * scene_manager.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "scene_manager.h"
#include "server_core/net/user_connection.h"
#include "theme0/scenes/main/main_scene_math/tile_grid_math.h"
#include "configuration/game_properties.h"
#include "theme0/scenes/main/process/tile_hovering.h"
#include "theme0/scenes/main/process/mouse_movement.h"
#include "server_core/world_structure/world.h"
#include "server_core/world_structure/world_area.h"
#include "server_core/world_structure/tile.h"
#include "server_core/core_game_objects/player.h"
#include "server_core/user_game_instance/scenes_core/scene.h"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace jod {
    scene_manager::scene_manager(
        user_connection &user_connection) : m_user_connection(user_connection){
        add_scene(
            "IntroScene",[] {
            },
            [&](websocket::stream<tcp::socket> &ws){
                m_user_connection.send_image_draw_instruction(
                    ws, "DefaultSceneBackground",
                    {0.0f, 0.0f, 1.0f, 1.0f});
                m_user_connection.send_image_draw_instruction(
                    ws, "JoDLogo",
                    {0.3f, 0.2f, 0.4f, 0.2f});
            },
            [] {
            },
            [&] {
                this->go_to("MainMenuScene");
            });
        add_scene(
            "MainMenuScene",
            [] {
            },
            [&](websocket::stream<tcp::socket> &ws){
                m_user_connection.send_image_draw_instruction(
                    ws, "DefaultSceneBackground",
                    {0.0f, 0.0f, 1.0f, 1.0f});
                m_user_connection.send_image_draw_instruction(
                    ws, "JoDLogo",
                    {0.4f, 0.1f, 0.2f, 0.1f});
            },
            [] {
            },
            [&] {
                this->go_to("MainScene");
            });
        add_scene(
            "MainScene",
            [&]{
                m_user_connection.m_tile_hovering->update();
                m_user_connection.m_mouse_movement->update();
            },
            [&](websocket::stream<tcp::socket> &ws){
                auto tile_size =
                    calculate_tile_size(m_user_connection.get_aspect_ratio());
                auto player_coordinate =
                    m_user_connection.m_player->m_coordinate;
                auto num_grid_rows = _<game_properties>().k_num_grid_rows;
                auto num_grid_cols = num_grid_rows;
                for (auto y = 0; y < num_grid_rows; y++){
                    for (auto x = 0; x < num_grid_cols; x++){
                        auto coord_x = player_coordinate.x -
                                       (num_grid_cols - 1) / 2 + x;
                        auto coord_y = player_coordinate.y -
                                       (num_grid_rows - 1) / 2 + y;
                        if (coord_x < 0 || coord_y < 0 || coord_x >= 100 ||
                            coord_y >= 100) continue;
                        auto tile =
                            _<world>().m_current_world_area->m_tiles[coord_x][
                                coord_y];
                        m_user_connection.send_image_draw_instruction(
                            ws,
                            tile->m_ground,
                            {x * tile_size.w, y * tile_size.h, tile_size.w,
                             tile_size.h});
                        if (coord_x ==
                            m_user_connection.m_tile_hovering->
                            m_hovered_coordinate.x &&
                            coord_y ==
                            m_user_connection.m_tile_hovering->
                            m_hovered_coordinate.y){
                            m_user_connection.send_image_draw_instruction(
                                ws,
                                "HoveredTile",
                                {x * tile_size.w, y * tile_size.h, tile_size.w,
                                 tile_size.h});
                        }
                        if (coord_x == player_coordinate.x &&
                            coord_y == player_coordinate.y){
                            m_user_connection.send_image_draw_instruction(
                                ws, "Player", {
                            x * tile_size.w, y * tile_size.h,
                            tile_size.w,
                            tile_size.h});
                        }
                    }
                }
            },
            [] {
            },
            [] {
            });
        go_to("IntroScene");
    }
    
    void
    scene_manager::update_current_scene(){
        if (m_scenes.contains(m_current_scene))
            m_scenes.at(m_current_scene).update();
    }
    
    void
    scene_manager::render_current_scene(websocket::stream<tcp::socket> &ws){
        if (m_scenes.contains(m_current_scene))
            m_scenes.at(m_current_scene).render(ws);
    }
    
    void
    scene_manager::on_key_down_current_scene(){
        if (m_scenes.contains(m_current_scene))
            m_scenes.at(m_current_scene).on_key_down();
    }
    
    void
    scene_manager::on_mouse_down_current_scene(){
        if (m_scenes.contains(m_current_scene))
            m_scenes.at(m_current_scene).on_mouse_down();
    }
    
    void
    scene_manager::go_to(std::string_view scene_name){
        m_current_scene = jod::hash(scene_name);
    }
    
    void
    scene_manager::add_scene(
        std::string_view scene_name,
        std::function<void()> update_action,
        std::function<void(websocket::stream<tcp::socket> &)> render_action,
        std::function<void()> key_down_action,
        std::function<void()> mouse_down_action){
        m_scenes.insert(
            {jod::hash(scene_name),
             {update_action, render_action, key_down_action,
              mouse_down_action}});
    }
}