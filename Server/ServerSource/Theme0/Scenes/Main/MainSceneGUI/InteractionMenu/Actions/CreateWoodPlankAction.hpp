/*
 * ChopAction.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "ObjectsPile.hpp"
#include "Object.hpp"

namespace JoD {
namespace Actions {
/// Action for creating wood planks out of wood logs.
    auto createWoodPlankAction =
        [] (Point clickedCoord) {
// Get tile.
            auto tile =
                _<World>().GetCurrWorldArea()->GetTile(
                    clickedCoord);
// Find wood log object, and replace 1 quantity of it with a wood plank.
            for (auto object : tile->GetObjectsPile().GetObjects()){
                if (object->GetType() == Hash("ObjectWoodLog")){
                    object->DecreaseQuantity(1);
                    if (object->GetQuantity() == 0)
                        tile->GetObjectsPile().RemoveObject(object);
                    tile->GetObjectsPile().AddObject("ObjectWoodPlank", 1);
                    break;
                }
            }
        };
}
}
