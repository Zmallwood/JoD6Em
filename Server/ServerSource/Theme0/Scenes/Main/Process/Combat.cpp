/*
 * Combat.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Combat.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "CreatureTargeting.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/Object.hpp"
#include "ServerCore/ServerWide/WorldStructure/Creature.hpp"
#include "ServerCore/ServerWide/WorldStructure/ObjectsPile.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"

namespace JoD {
    
    void Combat::Update(UserID userID) {
        
        auto player =
            _<EngineGet>().GetPlayer(userID);
        
        auto creatureTargeting =
            static_cast<CreatureTargeting*>(
                _<EngineGet>().GetSceneManager(userID)->GetScene<MainScene>(
                    "MainScene")->GetComponent(
                    MainSceneComponents::
                    CreatureTargeting));
        
        if (creatureTargeting->GetTargetedCreature()) {
            
            const auto &worldArea = _<World>().GetCurrentWorldArea();
            const auto pos =
                worldArea->GetCreatureCoord(
                    creatureTargeting->GetTargetedCreature()).value();
            
            auto playerCoord = player->GetCoord();
            
            auto absDx = std::abs(pos.x - playerCoord.x);
            auto absDy = std::abs(pos.y - playerCoord.y);
            
            if (absDx <= 1 && absDy <= 1) {
                
                if (Now() > player->GetTicksLastAttackOnOther() +
                    Duration(
                        Millis(
                            static_cast<int>(
                                1000/
                                player->GetAttackSpeed())))) {
                    
                    
                    
                    player->SetTicksLastAttackOnOther(Now());
                    
                    creatureTargeting->GetTargetedCreature()->Hit(1);
                    
                    worldArea->GetTile(pos)->SetGroundCover(
                        Hash(
                            "GroundCoverPoolOfBlood"));
                    
                    if (creatureTargeting->GetTargetedCreature()->IsDead()) {
                        
                        if (false ==
                            worldArea->GetTile(
                                pos)->GetObjectsPile().HasObjectOfType(
                                "ObjectBoneRemains")){
                            worldArea->GetTile(pos)->GetObjectsPile().AddObject("ObjectBoneRemains");
                        }
                        
                        player->AddExperience(
                            creatureTargeting->GetTargetedCreature()->GetExp());
                        
                        worldArea->RemoveCreaturePosition(
                            creatureTargeting->GetTargetedCreature());
                        
                        creatureTargeting->SetTargetedCreature(nullptr);
                        
                        worldArea->GetTile(pos)->SetCreature(nullptr);
                        
                    }
                }
            }
        }
    }
}