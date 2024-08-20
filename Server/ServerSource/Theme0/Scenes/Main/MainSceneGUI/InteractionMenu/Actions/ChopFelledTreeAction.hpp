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
auto chopFelledTreeAction =
    [] (Point clickedCoord) {
        auto tile =
            _<World>().GetCurrWorldArea()->GetTile(
                clickedCoord);
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