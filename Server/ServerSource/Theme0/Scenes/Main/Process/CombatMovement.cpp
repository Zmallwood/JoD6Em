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
        const std::shared_ptr<Player> player =
            m_userConnection.m_userGameInstanceEngine->m_player;
        
        const std::shared_ptr<MobTargeting> mobTargeting =
            std::static_pointer_cast<MobTargeting>(
                m_mainScene.m_components.at(
                    MainSceneComponents::
                    MobTargeting));
        
        if (mobTargeting->m_targetedCreature) {
            
            const auto worldArea = _<World>().m_currentWorldArea;
            const auto pos =
                worldArea->m_mobPositions.at(mobTargeting->m_targetedCreature);
            
            if (Now() > player->m_ticksLastMove +
                Duration(
                    Millis(
                        static_cast<int>(
                            1000/
                            player->m_movementSpeed)))) {
                
                const auto dx = pos.x - player->m_coordinate.x;
                const auto dy = pos.y - player->m_coordinate.y;
                
                if (dx < 0 && dy < 0) {
                    
                    player->TryMoveNorthWest();
                }else if (dx == 0 && dy < 0) {
                    
                    player->TryMoveNorth();
                }else if (dx > 0 && dy < 0) {
                    
                    player->TryMoveNorthEast();
                }else if (dx > 0 && dy == 0) {
                    
                    player->TryMoveEast();
                }else if (dx > 0 && dy > 0) {
                    
                    player->TryMoveSouthEast();
                }else if (dx == 0 && dy > 0) {
                    
                    player->TryMoveSouth();
                }else if (dx < 0 && dy > 0) {
                    
                    player->TryMoveSouthWest();
                }else if (dx < 0 && dy == 0) {
                    
                    player->TryMoveWest();
                }
                
                player->m_ticksLastMove = Now();
            }
        }
    }
}