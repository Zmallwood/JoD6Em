/*
 * BeginProcessWorld.cpp
 *
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
    
    std::thread(&RunWorldProcessingLoop).detach();
}

namespace {

void RunWorldProcessingLoop() {
    
    TimePoint timeLastUpdate = Now();
    
    const auto updateInterval = Duration(Millis(800));
    
    while (true) {
        
        if (Now() > timeLastUpdate + updateInterval) {
            
            timeLastUpdate = Now();
            
            UpdateMoveCreatureGroups();
            
            auto worldArea = _<World>().GetCurrWorldArea();
            
            for (auto y = 0; y < worldArea->GetSize().h; y++) {
                
                for (auto x = 0; x < worldArea->GetSize().w; x++) {
                    
                    UpdateTile({x, y});
                }
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }
}
}

namespace {

void UpdateTile(Point coord) {
    
    auto worldArea = _<World>().GetCurrWorldArea();
    
    auto tile = worldArea->GetTile(coord.x, coord.y);
    
    UpdateObjects(tile);
    
    UpdateNPCs(tile, coord);
    
    auto creature = tile->GetCreature();
    
    if (creature) {
        
        if (creature->GetType() == Hash("CreatureCow")) {
            
            UpdateAnimalsEating(tile);
        }
        
        UpdateCreaturesPathFollowing(tile, coord);
    }
}

}
}