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
/// Chop up a felled tree into wood logs.
    auto chopFelledTreeAction =
        [] (Point clickedCoord) {
// Get tile.
            auto tile =
                _<World>().GetCurrWorldArea()->GetTile(
                    clickedCoord);
// Find felled tree onject on tile and replace it with four wood logs.
            for (auto object : tile->GetObjectsPile().GetObjects()){
                if (object->GetType() == Hash("ObjectFelledTree")){
                    tile->GetObjectsPile().RemoveObject(object);
                    tile->GetObjectsPile().AddObject("ObjectWoodLog", 4);
                    break;
                }
            }
        };
}
}
