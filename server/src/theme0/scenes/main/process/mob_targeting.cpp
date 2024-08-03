/*
 * mob_targeting.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "mob_targeting.h"
#include "server_core/net/user_connection.h"
#include "server_core/user_game_instance/input/mouse/mouse_input.h"
#include "server_core/user_game_instance/input/mouse/mouse_button.h"
#include "server_core/user_game_instance/server_engine.h"
#include "tile_hovering.h"
#include "server_core/world_structure/world.h"
#include "server_core/world_structure/world_area.h"
#include "server_core/world_structure/tile.h"

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