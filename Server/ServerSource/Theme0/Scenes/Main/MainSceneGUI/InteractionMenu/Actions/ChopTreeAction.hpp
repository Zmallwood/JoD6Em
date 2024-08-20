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
/// Action for chopping down a tree.
auto chopTreeAction =
    [] (Point clickedCoord) {
// Get tile with the tree.
        auto tile =
            _<World>().GetCurrWorldArea()->GetTile(
                clickedCoord);
// Loop over all objects in tile.
        for (auto object : tile->GetObjectsPile().GetObjects()){
// If object is of any of the tree types.
            if (object->GetType() == Hash("ObjectTree1") ||
                object->GetType() == Hash("ObjectTree2")){
// Remove the tree object.
                tile->GetObjectsPile().RemoveObject(object);
// Add felled tree object.
                tile->GetObjectsPile().AddObject("ObjectFelledTree");
// Finished, can break the loop.
                break;
            }
        }
    };
}
}