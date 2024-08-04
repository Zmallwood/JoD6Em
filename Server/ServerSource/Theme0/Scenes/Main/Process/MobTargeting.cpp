/*
 * MobTargeting.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MobTargeting.h"
#include "ServerCore/Net/UserConnection.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.h"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.h"
#include "TileHovering.h"
#include "ServerCore/ServerWide/WorldStructure/World.h"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.h"
#include "ServerCore/ServerWide/WorldStructure/Tile.h"

namespace JoD {
    MobTargeting::MobTargeting(UserConnection& user_connection)
        : m_user_connection((user_connection)){
    }
    
    void MobTargeting::Update() {
        auto mouse_down =
            m_user_connection.m_user_game_instance_engine->m_mouse_input->m_right_button->
            IsPressedPickResult();
        auto hovered_tile =
            m_user_connection.m_tile_hovering->m_hovered_coordinate;
        if (mouse_down) {
            auto world_area = _<World>().m_current_world_area;
            auto tile = world_area->m_tiles[hovered_tile.x][hovered_tile.y];
            if (tile->m_mob) {
                m_targeted_creature = tile->m_mob;
            }
            else {
                m_targeted_creature = nullptr;
            }
        }
    }
}