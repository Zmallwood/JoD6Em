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
        auto mouseDown =
            m_userConnection.m_userGameInstanceEngine->m_mouseInput->
            m_rightButton->
            IsPressedPickResult();
        auto hoveredTile =
            tileHovering->m_hoveredCoordinate;
        if (mouseDown) {
            auto worldArea = _<World>().m_currentWorldArea;
            auto tile = worldArea->m_tiles[hoveredTile.x][hoveredTile.y];
            if (tile->m_mob) {
                m_targetedCreature = tile->m_mob;
            }else {
                m_targetedCreature = nullptr;
            }
        }
    }
}