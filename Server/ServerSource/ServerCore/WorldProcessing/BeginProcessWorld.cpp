/*
 * BeginProcessWorld.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "BeginProcessWorld.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Creature.hpp"
#include "SubProcess/UpdateMoveCreatureGroups.hpp"
#include "SubProcess/UpdateObjects.hpp"
#include "SubProcess/UpdateNPCs.hpp"
#include "SubProcess/UpdateAnimalsEating.hpp"
#include "SubProcess/UpdateCreaturesPathFollowing.hpp"

namespace JoD {
namespace {
void RunWorldProcessingLoop();
void UpdateTile(Point coord);
}

void BeginProcessWorld() {
// Start world processing loop in separate thread.
    std::thread(&RunWorldProcessingLoop).detach();
}

namespace {
void RunWorldProcessingLoop() {
// To keep track of update frequency.
    TimePoint timeLastUpdate = Now();
// How often the world will be processed.
    const auto updateInterval = Duration(Millis(800));
    while (true) {
        try {
// If time to process world...
            if (Now() > timeLastUpdate + updateInterval) {
                timeLastUpdate = Now();
// Move creature groups randomly around the worl darea.
                UpdateMoveCreatureGroups();
                auto worldArea = _<World>().GetCurrWorldArea();
// Update tiles in whole world area.
                for (auto y = 0; y < worldArea->GetSize().h; y++)
                    for (auto x = 0; x < worldArea->GetSize().w; x++)
                        UpdateTile({x, y});
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(70));
        }
        catch (const std::exception& ex) {
            std::cout << std::string("Exception in BeginProcessWorld(): ") + ex.what() << std::endl;
        }
    }
}
}

namespace {
void UpdateTile(Point coord) {
    auto worldArea = _<World>().GetCurrWorldArea();
    auto tile = worldArea->GetTile(coord.x, coord.y);
// Update all objects on tile.
    UpdateObjects(tile);
// UPdate NPC on tile if there is one.
    UpdateNPCs(tile, coord);
    auto creature = tile->GetCreature();
// Update creature if is one on tile.
    if (creature) {
// If creature is cow, update its eating grass from ground.
        if (creature->GetType() == Hash("CreatureCow"))
            UpdateAnimalsEating(tile);
// Make some creatures follow road paths.
        UpdateCreaturesPathFollowing(tile, coord);
    }
}
}
}