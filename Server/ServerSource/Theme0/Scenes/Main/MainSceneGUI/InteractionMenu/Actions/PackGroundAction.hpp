/*
 * ChopAction.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "ObjectsPile.hpp"

namespace JoD {
namespace Actions {
/// Action to pack ground.
    auto packGroundAction =
        [] (Point clickedCoord) {
// Get tile.
            auto tile =
                _<World>().GetCurrWorldArea()->GetTile(
                    clickedCoord);
// If no objects on tile, set the new ground type.
            if (tile->GetObjectsPile().GetNumObjects() == 0) {
                tile->SetGround("GroundTrail");
            }
        };
}
}
