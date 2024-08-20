/*
 * CombatMovement.cpp
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
// Get player object.
    auto player = _<EngineGet>().GetPlayer(userID);
// Get creature targeting component.
    auto creaTarg =
        static_cast<CreatureTargeting*>(
            _<EngineGet>().GetMainScene(userID)->GetComponent(
                MainSceneComponents::
                CreatureTargeting));
// Get targeted creature.
    auto targCrea = creaTarg->GetTargetedCreature();
// If targeted creature is valid.
    if (targCrea) {
// Get current world area.
        const auto &worldArea = _<World>().GetCurrWorldArea();
// Get coordinate of targeted creature.
        auto pos =
            worldArea->GetCreatureCoord(targCrea).value();
// If time for player to move.
        if (Now() > player->GetTimeLastMove() +
            Duration(
                Millis(
                    static_cast<int>(
                        1000/
                        player->GetMoveSpd())))) {
// Calculate deltas for the distance difference.
            auto dx = pos.x - player->GetCoord().x;
            auto dy = pos.y - player->GetCoord().y;
// Move in directio based on delta values.
            if (dx < 0 && dy < 0)
                player->TryMove(userID, Directions::NorthWest);
            else if (dx == 0 && dy < 0)
                player->TryMove(userID, Directions::North);
            else if (dx > 0 && dy < 0)
                player->TryMove(userID, Directions::NorthEast);
            else if (dx > 0 && dy == 0)
                player->TryMove(userID, Directions::East);
            else if (dx > 0 && dy > 0)
                player->TryMove(userID, Directions::SouthEast);
            else if (dx == 0 && dy > 0)
                player->TryMove(userID, Directions::South);
            else if (dx < 0 && dy > 0)
                player->TryMove(userID, Directions::SouthWest);
            else if (dx < 0 && dy == 0)
                player->TryMove(userID, Directions::West);
// Store time when move occured.
            player->SetTimeLastMove(Now());
        }
    }
}
}