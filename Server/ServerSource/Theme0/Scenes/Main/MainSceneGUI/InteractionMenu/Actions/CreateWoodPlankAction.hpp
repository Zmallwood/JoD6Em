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
auto createWoodPlankAction =
    [] (Point clickedCoord) {
        auto tile =
            _<World>().GetCurrWorldArea()->GetTile(
                clickedCoord);
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