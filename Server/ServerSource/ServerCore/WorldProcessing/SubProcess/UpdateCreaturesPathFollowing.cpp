/*
 * UpdateCreaturesPathFollowing.cpp
 *
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
        
        void MoveCreatureAlongRoadPath(Tile* creatureTile, Point coord);
    }
    
    void UpdateCreaturesPathFollowing(Tile* tile, Point coord) {
        
        auto creature = tile->GetCreature();
        
        if (creature->GetIsFollowingPath()) {
            
            if (Now() > creature->GetTimeLastMove() +
                Duration(
                    Millis(
                        static_cast<int>(1000/
                                         creature->GetMovementSpeed())))){
                
                MoveCreatureAlongRoadPath(tile, coord);
                
                creature->SetTimeLastMove(Now());
            }
        }
    }
    
    namespace {
        
        void MoveCreatureAlongRoadPath(Tile* creatureTile, Point coord) {
            
            auto worldArea = _<World>().GetCurrentWorldArea();
            
            auto creature = creatureTile->GetCreature();
            
            for (auto it = worldArea->m_roadPath.points.begin();
                 it != worldArea->m_roadPath.points.end();
                 it++) {
                
                if (it->x == coord.x && it->y == coord.y) {
                    
                    it++;
                    
                    if (it == worldArea->m_roadPath.points.end()) {
                        
                        auto beginningTile =
                            worldArea->GetTile(
                                worldArea->
                                m_roadPath.points[0]);
                        
                        beginningTile->SetCreature(
                            creature);
                        
                        worldArea->GetTile(
                            coord.x,
                            coord.y)->SetCreature(
                            nullptr);
                        
                        worldArea->
                        RemoveCreaturePosition(
                            creature);
                        
                        worldArea->
                        RegisterCreaturePosition(
                            creature,
                            worldArea->m_roadPath.
                            points[0]);
                        
                        break;
                    }
                    
                    auto newTile =
                        worldArea->GetTile(
                            it->x,
                            it->y);
                    
                    if (newTile && newTile->GetCreature() == nullptr) {
                        
                        newTile->SetCreature(
                            creature);
                        
                        worldArea->GetTile(
                            coord.x,
                            coord.y)->SetCreature(
                            nullptr);
                        
                        worldArea->
                        RemoveCreaturePosition(
                            creature);
                        
                        worldArea->
                        RegisterCreaturePosition(
                            creature,
                            {it->x,
                             it->y});
                    }
                    
                    if (creature->GetConnectedObject()){
                        
                        auto objectCoord =
                            creature->
                            GetConnectedObject()->
                            objectCoord;
                        
                        auto objectTile =
                            worldArea->GetTile(
                                objectCoord);
                        
                        for (auto object :
                             objectTile->
                             GetObjectsPile().
                             GetObjects()) {
                            
                            if (object ==
                                creature->
                                GetConnectedObject()
                                ->connectedObject) {
                                
                                auto oldTile =
                                    worldArea->
                                    GetTile(
                                        creature->
                                        GetConnectedObject()
                                        ->
                                        objectCoord);
                                creatureTile->GetObjectsPile()
                                .AddObject(
                                    std::shared_ptr<
                                        Object>(
                                        object));
                                oldTile->
                                GetObjectsPile().
                                RemoveObject(
                                    object);
                                
                                auto connectedObject
                                    =
                                        ConnectedObject
                                    {.
                                     connectedObject
                                         = object,
                                     .objectCoord =
                                         coord};
                                creature->
                                SetConnectedObject(
                                    connectedObject);
                                
                                break;
                            }
                        }
                    }
                    
                }
            }
        }
    }
}