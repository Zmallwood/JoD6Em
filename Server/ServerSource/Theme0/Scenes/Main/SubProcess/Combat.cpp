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
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Object.hpp"
#include "Creature.hpp"
#include "ObjectsPile.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/UserGameInstance/TextOutput/TextMessages.hpp"

namespace JoD {

void Combat::Update(UserID userID) {
    
    auto player = _<EngineGet>().GetPlayer(userID);
    
    auto textMsgs = _<EngineGet>().GetTextMessages(userID);
    const auto &wArea = _<World>().GetCurrWorldArea();
    
    auto mainScene = _<EngineGet>().GetMainScene(userID);
    
    auto creaTarg = static_cast<CreatureTargeting*>(
        mainScene->GetComponent(
            MainSceneComponents::
            CreatureTargeting));
    
    auto targCrea = creaTarg->GetTargetedCreature();
    
    if (targCrea) {
        
        auto pos = wArea->GetCreatureCoord(targCrea).value();
        
        auto creaTile = wArea->GetTile(pos);
        
        auto playerCoord = player->GetCoord();
        
        auto absDx = std::abs(pos.x - playerCoord.x);
        auto absDy = std::abs(pos.y - playerCoord.y);
        
        if (absDx <= 1 && absDy <= 1) {
            
            if (player->GetTimerAttackOnOther().Tick(player->GetAtkSpd())) {
                
                auto damage = 1;
                
                targCrea->Hit(damage);
                
                targCrea->SetTargetedUserID(userID);
                
                textMsgs->Print(
                    "You hit creature for " +
                    std::to_string(damage) + " dmg.");
                
                creaTile->GetObjectsPile().AddObject(
                    "ObjectPoolOfBlood");
                
                if (targCrea->IsDead()) {
                    
                    if (false == creaTile->GetObjectsPile().HasObjectOfType(
                            "ObjectBoneRemains")){
                        
                        creaTile->GetObjectsPile().AddObject(
                            "ObjectBoneRemains");
                    }
                    
                    player->AddExperience(targCrea->GetExp());
                    
                    wArea->RemoveCreaturePosition(targCrea);
                    
                    creaTarg->SetTargetedCreature(nullptr);
                    
                    creaTile->SetCreature(nullptr);
                    
                }
            }
        }
    }
    
    auto &creaPositions = wArea->GetCreaturePositions();
    
    for (auto& entry : creaPositions) {
        
        auto crea = entry.first;
        auto coord = entry.second;
        
        if (crea->GetTargetedUserID() == userID) {
            
            auto absDx = std::abs(player->GetCoord().x - coord.x);
            auto absDy = std::abs(player->GetCoord().y - coord.y);
            
            if (absDx <= 1 && absDy <= 1) {
                
                if (crea->GetTimerAttackOnOther().Tick(crea->GetAttackSpeed())) {
                    
                    auto damage = 1;
                    
                    player->Hit(damage);
                    
                    if (player->GetHP() <= 0) {
                        
                        player->SetCoord({5,5});
                        player->SetDestCoord(std::nullopt);
                        player->SetHP(player->GetMaxHP());
                        player->ResetExperience();
                        creaTarg->SetTargetedCreature(nullptr);
                        textMsgs->Print(
                            "You have died! Your have lost all your experience.");
                    }
                }
            }
        }
    }
}

}