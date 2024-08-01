// mouse_movement.cpp
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
///////////////////////////////////////////////////////////

#include "mouse_movement.h"
#include "server_core/net/user_connection.h"
#include "server_core/user_game_instance/client_core.h"
#include "server_core/core_game_objects/player.h"
#include "tile_hovering.h"

namespace jod {
    mouse_movement::mouse_movement(user_connection &user_connection) : m_user_connection(user_connection){
    }
    
    void
    mouse_movement::update(){
        auto mouseDown =
            m_user_connection.m_serverEngine->m_mouseInput->m_leftButton->
            is_pressed_pick_result();
        auto player = m_user_connection.m_player;
        auto hoveredTile = m_user_connection.m_tileHovering->m_hoveredCoordinate;
        if (mouseDown)
            player->m_destination = hoveredTile;
        if (std::chrono::high_resolution_clock::now() >
            player->m_ticks_last_move + std::chrono::high_resolution_clock::duration(std::chrono::milliseconds(static_cast<int>(1000/player->m_movement_speed)))){
            if (player->m_destination.x != -1 && player->m_destination.y != -1){
                auto dx = player->m_destination.x - player->m_coord.x;
                auto dy = player->m_destination.y - player->m_coord.y;
                auto absdx = std::abs(dx);
                auto absdy = std::abs(dy);
                auto normx = 0;
                auto normy = 0;
                if (dx) normx = dx / absdx;
                if (dy) normy = dy / absdy;
                player->m_coord.x += normx;
                player->m_coord.y += normy;
            }
            player->m_ticks_last_move = std::chrono::high_resolution_clock::now();
        }
    }
}