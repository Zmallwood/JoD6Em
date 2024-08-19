/*
 * GenerateWater.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateWater.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"

namespace JoD {
void GenerateWater(WorldArea* worldArea) {
    const auto numLakes = 15;
    for (auto i = 0; i < numLakes; i++){
        const auto xCenter = rand() %
                             worldArea->GetSize().w;
        const auto yCenter = rand() %
                             worldArea->GetSize().h;
        const auto r = 3 + rand() % 11;
// Loop in the form of a square, but only consider the tiles inside the radius r.
        for (auto y = yCenter - r; y <= yCenter + r; y++){
            for (auto x = xCenter - r; x <= xCenter + r; x++){
// Coord outside world area , skip iteration.
                if (!worldArea->IsValidCoord({x, y})) continue;
                const auto dx = x - xCenter;
                const auto dy = y - yCenter;
// If the radius from center to tile is less or equal to desired radius r...
                if (dx * dx + dy * dy <= r * r) {
// Do the actual ground type setting.
                    worldArea->GetTile(x, y)->SetGround(
                        Hash("GroundWater"));
                }
            }
        }
    }
}
}