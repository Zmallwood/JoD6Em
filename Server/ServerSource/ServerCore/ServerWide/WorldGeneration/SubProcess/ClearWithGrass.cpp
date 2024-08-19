/*
 * ClearWithGrass.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClearWithGrass.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"

namespace JoD {
void ClearWithGrass(WorldArea* worldArea) {
// Iterate through all tiles in the tile grid.
    for (auto y = 0; y < worldArea->GetSize().h; y++)
        for (auto x = 0; x < worldArea->GetSize().w; x++)
// Set ground to grass type.
            worldArea->GetTile(x, y)->SetGround(Hash("GroundGrass"));
}
}