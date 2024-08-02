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
                m_user_connection.m_tileHovering->update();
                m_user_connection.m_mouseMovement->update();
            },
            [&](websocket::stream<tcp::socket> &ws){
                auto tileSize =
                    calc_tile_size(m_user_connection.get_aspect_ratio());
                auto playerCoord = m_user_connection.m_player->m_coord;
                auto numGridRows = _<game_properties>().numGridRows;
                auto numGridCols = numGridRows;
                for (auto y = 0; y < numGridRows; y++){
                    for (auto x = 0; x < numGridCols; x++){
                        auto coordX = playerCoord.x - (numGridCols - 1) / 2 + x;
                        auto coordY = playerCoord.y - (numGridRows - 1) / 2 + y;
                        if (coordX < 0 || coordY < 0 || coordX >= 100 ||
                            coordY >= 100) continue;
                        auto tile =
                            _<world>().m_currentWorldArea->m_tiles[coordX][
                                coordY];
                        m_user_connection.send_image_draw_instruction(
                            ws,
                            tile->m_ground,
                            {x * tileSize.w, y * tileSize.h, tileSize.w,
                             tileSize.h});
                        if (coordX ==
                            m_user_connection.m_tileHovering->
                            m_hoveredCoordinate.x &&
                            coordY ==
                            m_user_connection.m_tileHovering->
                            m_hoveredCoordinate.y){
                            m_user_connection.send_image_draw_instruction(
                                ws,
                                "HoveredTile",
                                {x * tileSize.w, y * tileSize.h, tileSize.w,
                                 tileSize.h});
                        }
                        if (coordX == playerCoord.x && coordY == playerCoord.y){
                            m_user_connection.send_image_draw_instruction(
                                ws, "Player", {
                            x * tileSize.w, y * tileSize.h,
                            tileSize.w,
                            tileSize.h});
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
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).update();
    }
    
    void
    scene_manager::render_current_scene(websocket::stream<tcp::socket> &ws){
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).render(ws);
    }
    
    void
    scene_manager::on_key_down_current_scene(){
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).on_key_down();
    }
    
    void
    scene_manager::on_mouse_down_current_scene(){
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).on_mouse_down();
    }
    
    void
    scene_manager::go_to(std::string_view sceneName){
        m_currentScene = jod::hash(sceneName);
    }
    
    void
    scene_manager::add_scene(
        std::string_view sceneName,
        std::function<void()> updateAction,
        std::function<void(websocket::stream<tcp::socket> &)> renderAction,
        std::function<void()> keyDownAction,
        std::function<void()> mouseDownAction){
        m_scenes.insert(
            {jod::hash(sceneName),
             {updateAction, renderAction, keyDownAction,
              mouseDownAction}});
    }
}