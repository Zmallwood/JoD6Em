/*
 * mob_targeting.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "mob_targeting.h"
#include "ServerCore/Net/user_connection.h"
#include "ServerCore/UserGameInstance/Input/Mouse/mouse_input.h"
#include "ServerCore/UserGameInstance/Input/Mouse/mouse_button.h"
#include "ServerCore/UserGameInstance/server_engine.h"
#include "tile_hovering.h"
#include "ServerCore/WorldStructure/world.h"
#include "ServerCore/WorldStructure/world_area.h"
#include "ServerCore/WorldStructure/tile.h"

namespace jod {
    mob_targeting::mob_targeting(user_connection& user_connection)
        : m_user_connection((user_connection)){
    }
    
    void mob_targeting::update() {
        auto mouse_down =
            m_user_connection.m_server_engine->m_mouse_input->m_right_button->
            is_pressed_pick_result();
        auto hovered_tile =
            m_user_connection.m_tile_hovering->m_hovered_coordinate;
        if (mouse_down) {
            auto world_area = _<world>().m_current_world_area;
            auto tile = world_area->m_tiles[hovered_tile.x][hovered_tile.y];
            if (tile->m_creature) {
                m_targeted_creature = tile->m_creature;
            }
            else {
                m_targeted_creature = nullptr;
            }
        }
    }
}