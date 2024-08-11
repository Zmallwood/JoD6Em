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
#include "ServerCore/ServerWide/WorldStructure/Mob.hpp"
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
                    
                    auto &mobGroups = worldArea->m_mobGroups;
                    
                    for (auto &mobGroup : mobGroups) {
                        
                        auto dx = mobGroup.m_destCoord.x -
                                  mobGroup.m_coordinate.x;
                        auto dy = mobGroup.m_destCoord.y -
                                  mobGroup.m_coordinate.y;
                        
                        if (dx == 0 && dy == 0) {
                            
                            mobGroup.m_destCoord = {rand() % 100, rand() % 100};
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
                        
                        mobGroup.m_coordinate.x += normX;
                        mobGroup.m_coordinate.y += normY;
                        
                        for (auto mob : mobGroup.m_mobs) {
                            
                            auto pos = worldArea->GetMobCoord(mob);
                            
                            if (pos.has_value()) {
                                
                                const int k_maxMobGroupRadius = 4;
                                
                                auto dx = mobGroup.m_coordinate.x + rand() %
                                          k_maxMobGroupRadius - rand() %
                                          k_maxMobGroupRadius - pos.value().x;
                                auto dy = mobGroup.m_coordinate.y + rand() %
                                          k_maxMobGroupRadius - rand() %
                                          k_maxMobGroupRadius - pos.value().y;
                                
                                
                                if (dx*dx + dy*dy >
                                    k_maxMobGroupRadius*k_maxMobGroupRadius){
                                    
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
                                    
                                    if (newTile->GetMob() == nullptr) {
                                        
                                        newTile->SetMob(mob);
                                        worldArea->GetTile(pos.value())->SetMob(
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
                            
                            auto mob = tile->GetMob();
                            
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
                                                 worldArea->m_mobGroups.begin();
                                             groupIt !=
                                             worldArea->m_mobGroups.end() && goOn;
                                             groupIt++) {
                                            
                                            for (auto it =
                                                     groupIt->m_mobs.begin();
                                                 it != groupIt->m_mobs.end();
                                                 it++) {
                                                
                                                if (*it == tile->GetMob()) {
                                                    
                                                    groupIt->m_mobs.erase(it);
                                                    goOn = false;
                                                    break;
                                                }
                                            }
                                        }
                                        
                                        worldArea->RemoveMobPosition(
                                            tile->GetMob());
                                        
                                        tile->SetMob(nullptr);
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