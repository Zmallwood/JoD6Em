/*
 * MobTargeting.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MobTargeting.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"
#include "TileHovering.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"

namespace JoD {
    void MobTargeting::Update() {
        auto tileHovering =
            std::static_pointer_cast<TileHovering>(
                m_mainScene.m_components.at(
                    MainSceneComponents::
                    TileHovering));
        auto mouse_down =
            m_userConnection.m_user_game_instance_engine->m_mouse_input->
            m_right_button->
            IsPressedPickResult();
        auto hovered_tile =
            tileHovering->m_hovered_coordinate;
        if (mouse_down) {
            auto world_area = _<World>().m_current_world_area;
            auto tile = world_area->m_tiles[hovered_tile.x][hovered_tile.y];
            if (tile->m_mob) {
                m_targeted_creature = tile->m_mob;
            }else {
                m_targeted_creature = nullptr;
            }
        }
    }
}