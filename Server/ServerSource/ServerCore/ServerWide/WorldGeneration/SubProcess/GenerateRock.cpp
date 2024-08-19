/*
 * GenerateRock.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateRock.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"

namespace JoD {
void GenerateRock(WorldArea* worldArea) {
    auto numRockAreas = 20;
    for (auto i = 0; i < numRockAreas; i++) {
        auto xCenter = rand() % worldArea->GetSize().w;
        auto yCenter = rand() % worldArea->GetSize().h;
        auto r = 3 + rand() % 8;
// Loop in the form a square, but only consider tiles within the radius r.
        for (auto y = yCenter - r; y <= yCenter + r; y++) {
            for (auto x = xCenter - r; x <= xCenter + r; x++) {
// Coord outside world area, skip iteration.
                if (!worldArea->IsValidCoord(x, y)) continue;
                auto dx = x - xCenter;
                auto dy = y - yCenter;
// If radius from center to tile is less than or equal to the desired radius r...
                if (dx*dx + dy*dy <= r*r) {
                    auto tile = worldArea->GetTile(x, y);
// Elevation condition.
                    if (tile->GetElevation() > 2) {
// Do the ground setting.
                        tile->SetGround("GroundRock");
                    }
                }
            }
        }
    }
}
}