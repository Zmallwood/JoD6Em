/*
 * CombatMovement.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "CombatMovement.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "MobTargeting.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"

namespace JoD {
    void CombatMovement::Update() {
        auto player = m_userConnection.m_userGameInstanceEngine->m_player;
        
        auto mobTargeting =
            std::static_pointer_cast<MobTargeting>(
                m_mainScene.m_components.at(
                    MainSceneComponents::
                    MobTargeting));
        
        if (mobTargeting->m_targetedCreature) {
            
            auto worldArea = _<World>().m_currentWorldArea;
            auto pos =
                worldArea->m_mobPositions.at(mobTargeting->m_targetedCreature);
            
            if (Now() > player->m_ticksLastMove +
                Duration(
                    Millis(
                        static_cast<int>(1000/
                                         player->m_movementSpeed)))) {
                
                auto dx = pos.x - player->m_coordinate.x;
                auto dy = pos.y - player->m_coordinate.y;
                
                auto absDx = std::abs(dx);
                auto absDy = std::abs(dy);
                
                auto normX = 0;
                auto normY = 0;
                
                if (dx) {
                    normX = dx/absDx;
                }
                
                if (dy) {
                    normY = dy/absDy;
                }
                
                player->m_coordinate.x += normX;
                player->m_coordinate.y += normY;
                
                player->m_ticksLastMove = Now();
            }
        }
    }
}