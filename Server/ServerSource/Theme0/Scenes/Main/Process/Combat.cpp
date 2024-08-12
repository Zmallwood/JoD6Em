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
#include "ServerCore/UserGameInstance/TextOutput/TextMessages.hpp"

namespace JoD {
    
    void Combat::Update(UserID userID) {
        
        auto player =
            _<EngineGet>().GetPlayer(userID);
        
        auto textMessages = _<EngineGet>().GetTextMessages(userID);
        const auto &worldArea = _<World>().GetCurrentWorldArea();
        
        auto creatureTargeting =
            static_cast<CreatureTargeting*>(
                _<EngineGet>().GetSceneManager(userID)->GetScene<MainScene>(
                    "MainScene")->GetComponent(
                    MainSceneComponents::
                    CreatureTargeting));
        
        if (creatureTargeting->GetTargetedCreature()) {
            
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
                    
                    auto damage = 1;
                    
                    creatureTargeting->GetTargetedCreature()->Hit(damage);
                    
                    creatureTargeting->GetTargetedCreature()->SetTargetedUserID(
                        userID);
                    
                    textMessages->Print(
                        "You hit creature for " +
                        std::to_string(damage) + " dmg.");
                    
                    worldArea->GetTile(pos)->SetGroundCover(
                        Hash(
                            "GroundCoverPoolOfBlood"));
                    
                    if (creatureTargeting->GetTargetedCreature()->IsDead()) {
                        
                        if (false ==
                            worldArea->GetTile(
                                pos)->GetObjectsPile().HasObjectOfType(
                                "ObjectBoneRemains")){
                            worldArea->GetTile(pos)->GetObjectsPile().AddObject(
                                "ObjectBoneRemains");
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
        
        const auto &creaturePositions = worldArea->GetCreaturePositions();
        
        for (auto& entry : creaturePositions) {
            
            auto creature = entry.first;
            auto coord = entry.second;
            
            if (creature->GetTargetedUserID() == userID) {
                
                auto absDx = std::abs(player->GetCoord().x - coord.x);
                auto absDy = std::abs(player->GetCoord().y - coord.y);
                
                if (absDx <= 1 && absDy <= 1) {
                    
                    if (Now() >
                        creature->GetTicksLastAttackOnOther() + Duration(
                            Millis(
                                static_cast<int>(
                                    1000/
                                    creature->GetAttackSpeed())))) {
                        
                        auto damage = 1;
                        
                        player->Hit(damage);
                        
                        creature->SetTicksLastAttackOnOther(Now());
                    }
                }
            }
        }
    }
}