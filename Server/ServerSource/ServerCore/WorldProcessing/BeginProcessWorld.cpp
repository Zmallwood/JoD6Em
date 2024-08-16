/*
 * BeginProcessWorld.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "BeginProcessWorld.hpp"
#include "Common/Aliases.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Creature.hpp"
#include "Object.hpp"
#include "ObjectsPile.hpp"

namespace JoD {
    
    namespace {
        
        void RunWorldProcessingLoop();
        
        static constexpr Duration k_remainsStayDuration {Millis(5000)};
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
                    
                    auto worldArea = _<World>().GetCurrentWorldArea();
                    
                    auto &creatureGroups = worldArea->m_creatureGroups;
                    
                    for (auto &creatureGroup : creatureGroups) {
                        
                        auto dx = creatureGroup.m_destCoord.x -
                                  creatureGroup.m_coord.x;
                        auto dy = creatureGroup.m_destCoord.y -
                                  creatureGroup.m_coord.y;
                        
                        if (dx == 0 && dy == 0) {
                            
                            creatureGroup.m_destCoord = {rand() % 100,
                                                         rand() % 100};
                        }
                        
                        auto absDx = std::abs(dx);
                        auto absDy = std::abs(dy);
                        
                        auto normX = 0;
                        auto normY = 0;
                        
                        if (dx) {
                            
                            normX = dx/absDx;
                        }
                        
                        if (dy) {
                            
                            normY = dy/absDy;
                        }
                        
                        creatureGroup.m_coord.x += normX;
                        creatureGroup.m_coord.y += normY;
                        
                        for (auto creature : creatureGroup.m_creatures) {
                            
                            auto pos = worldArea->GetCreatureCoord(creature);
                            
                            if (pos.has_value()) {
                                
                                const int k_maxCreatureGroupRadius = 4;
                                
                                auto dx = creatureGroup.m_coord.x -
                                          pos.value().x;
                                auto dy = creatureGroup.m_coord.y -
                                          pos.value().y;
                                
                                
                                if (dx*dx + dy*dy >
                                    k_maxCreatureGroupRadius*
                                    k_maxCreatureGroupRadius){
                                    
                                    dx +=  +rand() %
                                          k_maxCreatureGroupRadius - rand() %
                                          k_maxCreatureGroupRadius;
                                    
                                    dy +=  +rand() %
                                          k_maxCreatureGroupRadius - rand() %
                                          k_maxCreatureGroupRadius;
                                    
                                    auto absDx = std::abs(dx);
                                    auto absDy = std::abs(dy);
                                    
                                    auto normX = 0;
                                    auto normY = 0;
                                    
                                    if (dx) {
                                        
                                        normX = dx/absDx;
                                    }
                                    
                                    if (dy) {
                                        
                                        normY = dy/absDy;
                                    }
                                    
                                    auto newX = pos.value().x + normX;
                                    auto newY = pos.value().y + normY;
                                    
                                    auto newTile = worldArea->GetTile(
                                        newX,
                                        newY);
                                    
                                    if (newTile &&
                                        newTile->GetCreature() == nullptr) {
                                        
                                        newTile->SetCreature(creature);
                                        worldArea->GetTile(
                                            pos.value())->SetCreature(
                                            nullptr);
                                        
                                        worldArea->RemoveCreaturePosition(
                                            creature);
                                        worldArea->RegisterCreaturePosition(
                                            creature,
                                            {newX,
                                             newY});
                                    }
                                }
                            }
                        }
                    }
                    
                    for (auto y = 0; y < worldArea->GetSize().h; y++) {
                        
                        for (auto x = 0; x < worldArea->GetSize().w; x++) {
                            
                            auto tile = worldArea->GetTile(x, y);
                            
                            auto objects = tile->GetObjectsPile().GetObjects();
                            
                            for (auto object : objects) {
                                
                                if (object->GetType() ==
                                    Hash("ObjectBoneRemains")) {
                                    
                                    if (Now() >
                                        object->GetCreationTime() +
                                        k_remainsStayDuration) {
                                        
                                        tile->GetObjectsPile().RemoveObject(
                                            object);
                                    }
                                }
                            }
                            
                            auto npc = tile->GetNPC();
                            
                            if (npc) {
                                
                                if (npc->GetIsFollowingPath()) {
                                    
                                    if (Now() >
                                        npc->GetTimeLastMove() +
                                        Duration(
                                            Millis(
                                                static_cast<int>(1000/
                                                                 npc
                                                                 ->
                                                                 GetMovementSpeed()))))
                                    {
                                        auto reversePath = worldArea->m_roadPath.points;
                                        
                                        std::reverse(reversePath.begin(), reversePath.end());
                                        
                                        for (auto it =
                                                 reversePath.
                                                 begin();
                                             it !=
                                             reversePath.end();
                                             it++) {
                                            
                                            if (it->x == x && it->y == y) {
                                                it++;
                                                
                                                if (it ==
                                                    reversePath
                                                    .end()) {
                                                    
                                                    auto beginningTile =
                                                        worldArea->GetTile(
                                                            reversePath[0]);
                                                    
                                                    beginningTile->SetNPC(
                                                        npc);
                                                    worldArea->GetTile(
                                                        x,
                                                        y)->SetNPC(
                                                        nullptr);
                                                    
                                                    break;
                                                }
                                                
                                                auto newTile =
                                                    worldArea->GetTile(
                                                        it->x,
                                                        it->y);
                                                
                                                if (newTile &&
                                                    newTile->GetNPC() ==
                                                    nullptr) {
                                                    
                                                    newTile->SetNPC(
                                                        npc);
                                                    worldArea->GetTile(
                                                        x,
                                                        y)->SetNPC(
                                                        nullptr);
                                                    
                                                }
                                                
                                                
                                            }
                                        }
                                        
                                        npc->SetTimeLastMove(Now());
                                    }
                                }
                            }
                            
                            auto creature = tile->GetCreature();
                            
                            if (creature) {
                                
                                if (creature->GetType() ==
                                    Hash("CreatureCow")) {
                                    
                                    for (auto object : objects) {
                                        
                                        if (object->GetType() ==
                                            Hash("ObjectGrass")) {
                                            
                                            object->SetDurability(
                                                object->GetDurability() - 1.0f);
                                            
                                            if (object->GetDurability() <=
                                                0.0f) {
                                                
                                                tile->GetObjectsPile().
                                                RemoveObject(object);
                                            }
                                        }
                                    }
                                }
                                
                                if (creature->GetIsFollowingPath()) {
                                    
                                    if (Now() >
                                        creature->GetTimeLastMove() +
                                        Duration(
                                            Millis(
                                                static_cast<int>(1000/
                                                                 creature
                                                                 ->
                                                                 GetMovementSpeed()))))
                                    {
                                        
                                        for (auto it =
                                                 worldArea->m_roadPath.points.
                                                 begin();
                                             it !=
                                             worldArea->m_roadPath.points.end();
                                             it++) {
                                            
                                            if (it->x == x && it->y == y) {
                                                it++;
                                                
                                                if (it ==
                                                    worldArea->m_roadPath.points
                                                    .end()) {
                                                    
                                                    auto beginningTile =
                                                        worldArea->GetTile(
                                                            worldArea->
                                                            m_roadPath.points[0]);
                                                    
                                                    beginningTile->SetCreature(
                                                        creature);
                                                    worldArea->GetTile(
                                                        x,
                                                        y)->SetCreature(
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
                                                
                                                if (newTile &&
                                                    newTile->GetCreature() ==
                                                    nullptr) {
                                                    
                                                    newTile->SetCreature(
                                                        creature);
                                                    worldArea->GetTile(
                                                        x,
                                                        y)->SetCreature(
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
                                                
                                                if (creature->GetConnectedObject())
                                                {
                                                    
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
                                                            tile->GetObjectsPile()
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
                                                                 {x, y}};
                                                            creature->
                                                            SetConnectedObject(
                                                                connectedObject);
                                                            
                                                            break;
                                                        }
                                                    }
                                                }
                                                
                                            }
                                        }
                                        
                                        creature->SetTimeLastMove(Now());
                                    }
                                }
                            }
                        }
                    }
                }
                
                std::this_thread::sleep_for(std::chrono::milliseconds(70));
            }
        }
    }
}