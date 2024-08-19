/*
 * GenerateCastleYard.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateCastleYard.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "ObjectsPile.hpp"

namespace JoD {
void GenerateCastleYard(WorldArea* worldArea) {
// Create cobble stone ground type.
    for (auto y = 0; y < 25; y++) {
        for (auto x = 0; x < 25; x++) {
            auto tile = worldArea->GetTile(x, y);
            tile->SetGround("GroundCobbleStone");
            tile->SetElevation(0);
        }
    }
// Create castle walls to the east.
    for (auto y = 0; y < 24; y++) {
        auto tile = worldArea->GetTile(25, y);
        tile->GetObjectsPile().AddObject("ObjectCastleWallE");
    }
// Create castle walls to the south.
    for (auto x = 0; x < 24; x++) {
        auto tile = worldArea->GetTile(x, 25);
        tile->GetObjectsPile().AddObject("ObjectCastleWallS");
    }
}
}