/*
 * MobTargeting.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MobTargeting.h"
#include "ServerCore/Net/UserConnection.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.h"
#include "ServerCore/UserGameInstance/ServerEngine.h"
#include "TileHovering.h"
#include "ServerCore/WorldStructure/World.h"
#include "ServerCore/WorldStructure/WorldArea.h"
#include "ServerCore/WorldStructure/Tile.h"

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