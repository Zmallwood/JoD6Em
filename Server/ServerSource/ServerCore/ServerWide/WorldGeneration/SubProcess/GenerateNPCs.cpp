/*
 * GenerateNPCs.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateNPCs.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "NPC.hpp"

namespace JoD {
void GenerateNPCs(WorldArea* worldArea) {
// Current tile step.
    auto tileStep = 0;
// Shift the tiles on which the NPCs are created.
    auto tileStepOffset = 12;
// Create NPC every x:th tile.
    auto npcCreationInterval = 18;
    for (auto y = 0; y < worldArea->GetSize().h; y++) {
        for (auto x = 0; x < worldArea->GetSize().w; x++){
            auto tile = worldArea->GetTile(x,y);
// Check if current tile is of road type.
            bool coordInRoadPath = false;
            for (auto p : worldArea->m_roadPath) {
                if (p.x == x && p.y == y) {
                    coordInRoadPath = true;
                    break;
                }
            }
            if (coordInRoadPath) {
// Only create NPC with an interval equal to npcCreationInterval.
                if (tileStep % npcCreationInterval ==
                    tileStepOffset) {
                    auto newNPC = std::make_unique<NPC>();
                    newNPC->SetIsFollowingPath(true);
                    tile->SetNPC(std::move(newNPC));
                }
                tileStep++;
            }
        }
    }
}
}