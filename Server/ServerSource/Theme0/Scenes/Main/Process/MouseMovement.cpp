/*
 * MouseMovement.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseMovement.h"
#include "ServerCore/Net/UserConnection.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.h"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.h"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.h"
#include "TileHovering.h"

namespace JoD {
    MouseMovement::MouseMovement(
        UserConnection &user_connection) : m_user_connection(user_connection){
    }
    
    void
    MouseMovement::Update(){
        auto mouse_down =
            m_user_connection.m_user_game_instance_engine->m_mouse_input->m_left_button->
            IsPressedPickResult();
        auto player = m_user_connection.m_player;
        auto hovered_tile =
            m_user_connection.m_tile_hovering->m_hovered_coordinate;
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