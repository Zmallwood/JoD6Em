/*
 * ChopAction.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "ObjectsPile.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"

namespace JoD {
namespace Actions {
/// Action to pack ground.
    auto climbLadderAction =
        [] (Point clickedCoord, UserID userID) {
// Get tile.
            auto tile =
                _<World>().GetCurrWorldArea()->GetTile(
                    clickedCoord);
// If no objects on tile, set the new ground type.
            if (tile->GetObjectsPile().HasObjectOfType("ObjectLadder")) {
                auto player = _<EngineGet>().GetPlayer(userID);
                
                player->IncreaseWorldFloor();
            }
        };
}
}
