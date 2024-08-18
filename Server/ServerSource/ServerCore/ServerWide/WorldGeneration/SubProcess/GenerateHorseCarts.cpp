/*
 * GenerateHorseCarts.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateHorseCarts.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Creature.hpp"
#include "Object.hpp"
#include "NPC.hpp"
#include "ObjectsPile.hpp"

namespace JoD {

void GenerateHorseCarts(WorldArea* worldArea) {
    
    auto tileStep = 0;
    auto tileStepOffset = 8;
    auto horseCreationInterval = 20;
    
// Loop over whole world area.
    
    for (auto y = 0; y < worldArea->GetSize().h; y++) {
        
        for (auto x = 0; x < worldArea->GetSize().w;
             x++){
            
// Dont consider tiles where x == 0, as there is no room for a cart then.
            if (x == 0) {
                
                continue;
            }
            
            auto tile = worldArea->GetTile(x,y);
            
// Check if current tile is of road type.
            if (tile->GetGround() == Hash("GroundSlabs")
                || tile->GetGround() == Hash("GroundTrail")
                || tile->GetGround() == Hash("Bridge")) {
                
// Only create horse with an interval equal to horseCreationInterval.
                if (tileStep % horseCreationInterval ==
                    tileStepOffset) {
                    
// Create new horse creature.
                    const auto newHorse =
                        std::make_shared<Creature>(
                            "CreatureHorse",
                            3);
                    
                    newHorse->SetIsFollowingPath(true);
                    
// Register the creatures position to the world area.
                    worldArea->RegisterCreaturePosition(newHorse, {x, y});
                    
// Add the new creature object to the tile its located at.
                    worldArea->GetTile(x, y)->SetCreature(newHorse);
                    
// Get west neighbour tile to create a cart there.
                    auto tileWest = worldArea->GetTile(x - 1, y);
                    tileWest->GetObjectsPile().Clear();
                    
// Create new cart object.
                    auto cart = std::make_shared<Object>("ObjectHorseCart");
                    
// Make it contain a NPC.
                    cart->SetContainedNPC(std::make_unique<NPC>());
                    
// Connect the cart to the horse.
                    newHorse->SetConnectedObject(
                        {.connectedObject = cart,
                         .objectCoord = {x - 1, y}});
                    
// Add the cart to the world area.
                    tileWest->GetObjectsPile().AddObject(cart);
                }
                
// Count steps taken.
                tileStep++;
            }
        }
    }
}

}