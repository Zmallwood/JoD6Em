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
auto packGroundAction =
    [] (Point clickedCoord) {
        auto tile =
            _<World>().GetCurrWorldArea()->GetTile(
                clickedCoord);
        if (tile->GetObjectsPile().GetNumObjects() == 0) {
            tile->SetGround("GroundTrail");
        }
    };
}
}