/*
 * UpdateCreaturesPathFollowing.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "UpdateCreaturesPathFollowing.hpp"
#include "Tile.hpp"
#include "Creature.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "ObjectsPile.hpp"

namespace JoD {

namespace {

// Move creature on a tile along a road path in the world area.
void MoveCreatureAlongRoadPath(Tile* creatureTile, Point coord);

}

void UpdateCreaturesPathFollowing(Tile* tile, Point coord) {
    
// Get creature on tile.
    auto creature = tile->GetCreature();
    
// Check if its following a road path.
    if (creature->GetIsFollowingPath()) {
        
// Check if its time for creature to move.
        if (Now() > creature->GetTimeLastMove() +
            Duration(
                Millis(
                    static_cast<int>(1000/
                                     creature->GetMoveSpd())))){
            
// Move it along the road path.
            MoveCreatureAlongRoadPath(tile, coord);
            
            // Save update time.
            creature->SetTimeLastMove(Now());
        }
    }
}

namespace {

void MoveCreatureAlongRoadPath(Tile* creatureTile, Point coord) {
    
    auto wArea = _<World>().GetCurrWorldArea();
    
    auto creature = creatureTile->GetCreature();
    
// Loop over road path points.
    for (auto it = wArea->m_roadPath.begin();
         it != wArea->m_roadPath.end(); it++) {
        
// If road point is the same coord as the creatures coord.
        if (it->x == coord.x && it->y == coord.y) {
            
// Go to the next road path ahead of creature.
            it++;
            
// If this road path point is the end point...
            if (it == wArea->m_roadPath.end()) {
                
// Get the first road path point.
                auto beginningTile =
                    wArea->GetTile(wArea->m_roadPath[0]);
                
// And move creature there.
                beginningTile->SetCreature(creature);
                
// Remove creature from old tile.
                wArea->GetTile(coord)->SetCreature(nullptr);
                
// And remove old position from world area storage.
                wArea->RemoveCreaturePosition(creature);
                
// And add the new creature position to world area storage.
                wArea->RegisterCreaturePosition(
                    creature,
                    wArea->m_roadPath[0]);
                
// Stop looping over road path points.
                break;
            }
            
// If next road path tile is not the end,
// just obtain the tile as usual.
            auto newTile = wArea->GetTile(it->x, it->y);
            
// If new tile is valid and dont already contains a creature...
            if (newTile && newTile->GetCreature() == nullptr) {
                
// Move the creature there.
                newTile->SetCreature(creature);
                
// And remove the creature from the old tile.
                wArea->GetTile(coord.x, coord.y)->SetCreature(nullptr);
                
// Remove the old creature coord from world area storae.
                wArea->RemoveCreaturePosition(creature);
                
// And add the new creature coord to the world area storage.
                wArea->RegisterCreaturePosition(
                    creature,
                    {it->x, it->y});
            }
            
// If the creature has an object, such as a cart, connected to it...
            if (creature->GetConnectedObject()){
                
// Get the coord of this object.
                auto objectCoord =
                    creature->GetConnectedObject()->objectCoord;
                
// And the tile its located at.
                auto objectTile = wArea->GetTile(objectCoord);
                
// Loop over all the objects on the tile.
                for (auto object :
                     objectTile->GetObjectsPile().GetObjects()) {
                    
// And find the seeked objects.
                    if (object ==
                        creature->GetConnectedObject()->connectedObject){
                        
// Get the old tile of the object.
                        auto oldTile = wArea->GetTile(objectCoord);
                        
// Add the object to the previous creature tile.
                        creatureTile->GetObjectsPile().AddObject(
                            std::shared_ptr<Object>(object));
                        
// Remove the object from the old tile.
                        oldTile->GetObjectsPile().RemoveObject(object);
                        
// Create new ConnectedObject object.
                        auto connectedObject =
                            ConnectedObject {.connectedObject = object,
                                             .objectCoord = coord};
                        
// And apply it to the creature.
                        creature->SetConnectedObject(connectedObject);
                        
                        break;
                    }
                }
            }
        }
    }
}

}
}