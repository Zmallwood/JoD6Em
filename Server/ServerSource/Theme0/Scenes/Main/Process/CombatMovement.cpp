/*
 * CombatMovement.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "CombatMovement.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "MobTargeting.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"

namespace JoD {
    void CombatMovement::Update() {
        const std::unique_ptr<Player> &player =
            m_engineInstance.Player();
        
        const std::shared_ptr<MobTargeting> mobTargeting =
            std::static_pointer_cast<MobTargeting>(
                m_mainScene.m_components.at(
                    MainSceneComponents::
                    MobTargeting));
        
        if (mobTargeting->m_targetedCreature) {
            
            const auto &worldArea = _<World>().GetCurrentWorldArea();
            const auto pos =
                worldArea->GetMobCoord(mobTargeting->m_targetedCreature).value();
            
            if (Now() > player->TicksLastMove() +
                Duration(
                    Millis(
                        static_cast<int>(
                            1000/
                            player->MovementSpeed())))) {
                
                const auto dx = pos.x - player->Coord().x;
                const auto dy = pos.y - player->Coord().y;
                
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
                
                player->SetTicksLastMove(Now());
            }
        }
    }
}