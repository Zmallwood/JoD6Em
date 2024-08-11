/*
 * BeginProcessWorld.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "BeginProcessWorld.hpp"
#include "Common/Aliases.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/Creature.hpp"
#include "ServerCore/ServerWide/WorldStructure/Object.hpp"
#include "ServerCore/ServerWide/WorldStructure/ObjectsPile.hpp"

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
            
            TimePoint ticksLastUpdate = Now();
            
            const auto updateInterval = Duration(Millis(3000));
            
            while (true) {
                
                if (Now() > ticksLastUpdate + updateInterval) {
                    
                    ticksLastUpdate = Now();
                    
                    auto worldArea = _<World>().GetCurrentWorldArea();
                    
                    auto &creatureGroups = worldArea->m_creatureGroups;
                    
                    for (auto &creatureGroup : creatureGroups) {
                        
                        auto dx = creatureGroup.m_destCoord.x -
                                  creatureGroup.m_coord.x;
                        auto dy = creatureGroup.m_destCoord.y -
                                  creatureGroup.m_coord.y;
                        
                        if (dx == 0 && dy == 0) {
                            
                            creatureGroup.m_destCoord = {rand() % 100, rand() % 100};
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
                        
                        for (auto mob : creatureGroup.m_creatures) {
                            
                            auto pos = worldArea->GetMobCoord(mob);
                            
                            if (pos.has_value()) {
                                
                                const int k_maxMobGroupRadius = 4;
                                
                                auto dx = creatureGroup.m_coord.x - pos.value().x;
                                auto dy = creatureGroup.m_coord.y - pos.value().y;
                                
                                
                                if (dx*dx + dy*dy >
                                    k_maxMobGroupRadius*k_maxMobGroupRadius){
                                        
                                        dx +=  + rand() %
                                          k_maxMobGroupRadius - rand() %
                                          k_maxMobGroupRadius;
                                          
                                          dy +=  + rand() %
                                          k_maxMobGroupRadius - rand() %
                                          k_maxMobGroupRadius;
                                    
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
                                    
                                    if (newTile->GetCreature() == nullptr) {
                                        
                                        newTile->SetCreature(mob);
                                        worldArea->GetTile(pos.value())->SetCreature(
                                            nullptr);
                                        
                                        worldArea->RemoveMobPosition(mob);
                                        worldArea->RegisterMobPosition(mob,
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
                            
                            auto mob = tile->GetCreature();
                            
                            if (mob) {
                                
                                if (mob->GetType() == Hash("MobCow")) {
                                    
                                    for (auto object : objects) {
                                        
                                        if (object->GetType() ==
                                            Hash("ObjectGrass")) {
                                            
                                            object->m_durability -= 1.0f;
                                            mob->m_hunger -= 0.01f;
                                            
                                            if (object->m_durability <= 0.0f) {
                                                
                                                tile->GetObjectsPile().
                                                RemoveObject(object);
                                            }
                                        }
                                    }
                                    
                                    mob->m_hunger += 0.01f;
                                    
                                    if (mob->m_hunger >= 1.0f) {
                                        
                                        if (false ==
                                            tile->GetObjectsPile().
                                            HasObjectOfType(
                                                "ObjectBoneRemains")){
                                            tile->GetObjectsPile().AddObject(
                                                "ObjectBoneRemains");
                                        }
                                        
                                        bool goOn = true;
                                        
                                        for (auto groupIt =
                                                 worldArea->m_creatureGroups.begin();
                                             groupIt !=
                                             worldArea->m_creatureGroups.end() && goOn;
                                             groupIt++) {
                                            
                                            for (auto it =
                                                     groupIt->m_creatures.begin();
                                                 it != groupIt->m_creatures.end();
                                                 it++) {
                                                
                                                if (*it == tile->GetCreature()) {
                                                    
                                                    groupIt->m_creatures.erase(it);
                                                    goOn = false;
                                                    break;
                                                }
                                            }
                                        }
                                        
                                        worldArea->RemoveMobPosition(
                                            tile->GetCreature());
                                        
                                        tile->SetCreature(nullptr);
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