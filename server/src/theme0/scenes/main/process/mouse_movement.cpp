/*
 * mouse_movement.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "mouse_movement.h"
#include "server_core/net/user_connection.h"
#include "server_core/user_game_instance/input/mouse/mouse_input.h"
#include "server_core/user_game_instance/input/mouse/mouse_button.h"
#include "server_core/user_game_instance/server_engine.h"
#include "server_core/core_game_objects/player.h"
#include "tile_hovering.h"

namespace jod {
    mouse_movement::mouse_movement(
        user_connection &user_connection) : m_user_connection(user_connection){
    }
    
    void
    mouse_movement::update(){
        auto mouse_down =
            m_user_connection.m_server_engine->m_mouse_input->m_left_button->
            is_pressed_pick_result();
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