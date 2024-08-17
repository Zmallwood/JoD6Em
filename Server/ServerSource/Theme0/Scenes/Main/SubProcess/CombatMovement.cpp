/*
 * CombatMovement.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "CombatMovement.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "CreatureTargeting.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    
void CombatMovement::Update(UserID userID) {
    auto player =
        _<EngineGet>().GetPlayer(userID);
    
    auto creatureTargeting =
        static_cast<CreatureTargeting*>(
            _<EngineGet>().GetSceneManager(userID)->GetScene<MainScene>(
                "MainScene")->GetComponent(
                MainSceneComponents::
                CreatureTargeting));
    
    if (creatureTargeting->GetTargetedCreature()) {
        
        const auto &worldArea = _<World>().GetCurrWorldArea();
        const auto pos =
            worldArea->GetCreatureCoord(
                creatureTargeting->GetTargetedCreature()).value();
        
        if (Now() > player->GetTimeLastMove() +
            Duration(
                Millis(
                    static_cast<int>(
                        1000/
                        player->GetMS())))) {
            
            const auto dx = pos.x - player->GetCoord().x;
            const auto dy = pos.y - player->GetCoord().y;
            
            if (dx < 0 && dy < 0) {
                
                player->TryMove(userID, Directions::NorthWest);
            }
            else if (dx == 0 && dy < 0) {
                
                player->TryMove(userID, Directions::North);
            }
            else if (dx > 0 && dy < 0) {
                
                player->TryMove(userID, Directions::NorthEast);
            }
            else if (dx > 0 && dy == 0) {
                
                player->TryMove(userID, Directions::East);
            }
            else if (dx > 0 && dy > 0) {
                
                player->TryMove(userID, Directions::SouthEast);
            }
            else if (dx == 0 && dy > 0) {
                
                player->TryMove(userID, Directions::South);
            }
            else if (dx < 0 && dy > 0) {
                
                player->TryMove(userID, Directions::SouthWest);
            }
            else if (dx < 0 && dy == 0) {
                
                player->TryMove(userID, Directions::West);
            }
            
            player->SetTimeLastMove(Now());
        }
    }
}

}