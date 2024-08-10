/*
 * CombatMovement.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "CombatMovement.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "MobTargeting.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    void CombatMovement::Update(UserID userID) {
        auto player =
            _<EngineGet>().GetPlayer(userID);
        
        auto mobTargeting =
            static_cast<MobTargeting*>(
                _<EngineGet>().GetSceneManager(userID)->GetScene<MainScene>("MainScene")->GetComponent(
                    MainSceneComponents::
                    MobTargeting));
        
        if (mobTargeting->GetTargetedCreature()) {
            
            const auto &worldArea = _<World>().GetCurrentWorldArea();
            const auto pos =
                worldArea->GetMobCoord(mobTargeting->GetTargetedCreature()).value();
            
            if (Now() > player->GetTicksLastMove() +
                Duration(
                    Millis(
                        static_cast<int>(
                            1000/
                            player->GetMovementSpeed())))) {
                
                const auto dx = pos.x - player->GetCoord().x;
                const auto dy = pos.y - player->GetCoord().y;
                
                if (dx < 0 && dy < 0) {
                    
                    player->TryMoveNorthWest(userID);
                }else if (dx == 0 && dy < 0) {
                    
                    player->TryMoveNorth(userID);
                }else if (dx > 0 && dy < 0) {
                    
                    player->TryMoveNorthEast(userID);
                }else if (dx > 0 && dy == 0) {
                    
                    player->TryMoveEast(userID);
                }else if (dx > 0 && dy > 0) {
                    
                    player->TryMoveSouthEast(userID);
                }else if (dx == 0 && dy > 0) {
                    
                    player->TryMoveSouth(userID);
                }else if (dx < 0 && dy > 0) {
                    
                    player->TryMoveSouthWest(userID);
                }else if (dx < 0 && dy == 0) {
                    
                    player->TryMoveWest(userID);
                }
                
                player->SetTicksLastMove(Now());
            }
        }
    }
}