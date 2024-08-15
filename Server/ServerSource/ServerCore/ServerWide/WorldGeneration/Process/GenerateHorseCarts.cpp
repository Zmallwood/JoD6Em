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
#include "Configuration/GameProperties.hpp"

namespace JoD {
    
    void GenerateHorseCarts(WorldArea* worldArea) {
        
        auto i = 0;
        auto horseOffset = 8;
        auto horseInterval = 20;
        
        for (auto y = 0; y < _<GameProperties>().GetWorldAreaSize().h; y++) {
            
            for (auto x = 0; x < _<GameProperties>().GetWorldAreaSize().w;
                 x++) {
                
                auto tile = worldArea->GetTile(x,y);
                
                if (tile->GetGround() == Hash("GroundSlabs")
                    || tile->GetGround() == Hash("GroundTrail")
                    || tile->GetGround() == Hash("Bridge")) {
                    
                    if (i % horseInterval == horseOffset) {
                        
                        const auto newHorse =
                            std::make_shared<Creature>(
                                "CreatureHorse",
                                3);
                        
                        // Register the creatures position to the world area.
                        worldArea->RegisterCreaturePosition(
                            newHorse,
                            {x, y});
                        
                        // Add the new creature object to the tile its located at.
                        worldArea->GetTile(x, y)->SetCreature(newHorse);
                        
                        auto tileW = worldArea->GetTile(x - 1, y);
                        
                        tileW->GetObjectsPile().Clear();
                        
                        auto cart = std::make_unique<Object>("ObjectHorseCart");
                        
                        cart->SetContainedNPC(std::make_unique<NPC>());
                        
                        newHorse->SetConnectedObject({.connectedObject = cart, .objectCoord = {x, y}});
                        
                        tileW->GetObjectsPile().AddObject(std::move(cart));
                    }
                    
                    i++;
                }
            }
        }
    }
}