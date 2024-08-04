/*
 * MouseMovement.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseMovement.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "TileHovering.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"

namespace JoD {
    void
    MouseMovement::Update(){
        auto tileHovering =
            std::static_pointer_cast<TileHovering>(
                m_mainScene.m_components.at(
                    MainSceneComponents::
                    TileHovering));
        auto mouse_down =
            m_userConnection.m_user_game_instance_engine->m_mouse_input->m_left_button->
            IsPressedPickResult();
        auto player = m_userConnection.m_player;
        auto hovered_tile =
            tileHovering->m_hovered_coordinate;
        if (mouse_down)
            player->m_destination = hovered_tile;
        if (std::chrono::high_resolution_clock::now() >
            player->m_ticks_last_move +
            std::chrono::high_resolution_clock::duration(
                std::chrono::milliseconds(static_cast<int>(1000/
                                                           player->
                                                           m_movement_speed)))){
            if (player->m_destination.x != -1 && player->m_destination.y != -1){
                auto dx = player->m_destination.x - player->m_coordinate.x;
                auto dy = player->m_destination.y - player->m_coordinate.y;
                auto abs_dx = std::abs(dx);
                auto abs_dy = std::abs(dy);
                auto norm_x = 0;
                auto norm_y = 0;
                if (dx) norm_x = dx / abs_dx;
                if (dy) norm_y = dy / abs_dy;
                player->m_coordinate.x += norm_x;
                player->m_coordinate.y += norm_y;
            }
            player->m_ticks_last_move =
                std::chrono::high_resolution_clock::now();
        }
    }
}