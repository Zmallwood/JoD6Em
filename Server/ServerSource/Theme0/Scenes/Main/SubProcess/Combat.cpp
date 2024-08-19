/*
 * Combat.cpp
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
    
// Get engine objects.
    auto player = _<EngineGet>().GetPlayer(userID);
    auto textMsgs = _<EngineGet>().GetTextMessages(userID);
    const auto &wArea = _<World>().GetCurrWorldArea();
    auto mainScene = _<EngineGet>().GetMainScene(userID);

// Get creature targeting component.    
    auto creaTarg = static_cast<CreatureTargeting*>(
        mainScene->GetComponent(
            MainSceneComponents::
            CreatureTargeting));
    
// Obtain targeted creature.
    auto targCrea = creaTarg->GetTargetedCreature();
    
// If any creature is targeted.
    if (targCrea) {
        
// Get coordinate of targeted creature.
        auto pos = wArea->GetCreatureCoord(targCrea).value();
        
// Get tiel of targeted creature.
        auto creaTile = wArea->GetTile(pos);
        
// Get coordiante of player.
        auto playerCoord = player->GetCoord();
        
// Calculate absolute distance components.
        auto absDx = std::abs(pos.x - playerCoord.x);
        auto absDy = std::abs(pos.y - playerCoord.y);
        
// If within melee range.
        if (absDx <= 1 && absDy <= 1) {
            
// When player attack is ready.
            if (player->GetTimerAttackOnOther().Tick(player->GetAtkSpd())) {
                
// Determine damage to inflict on creature.
                auto damage = 1;
                
// Hit creature.
                targCrea->Hit(damage);
                
// Make the creature target the user that attacked it.
                targCrea->SetTargetedUserID(userID);
                
// Notify about the hit and its damage.
                textMsgs->Print(
                    "You hit creature for " +
                    std::to_string(damage) + " dmg.");
                
// Create pool of blood on ground every hit.
                creaTile->GetObjectsPile().AddObject(
                    "ObjectPoolOfBlood");
                
// If creature is dead.
                if (targCrea->IsDead()) {
                    
// Create bone remains object if doesnt already exists.
                    if (false == creaTile->GetObjectsPile().HasObjectOfType(
                            "ObjectBoneRemains")){
                        
                        creaTile->GetObjectsPile().AddObject(
                            "ObjectBoneRemains");
                    }
                    
// Add exp to player, amount obtained from defeated creature.
                    player->AddExp(targCrea->GetExp());
                    
// Remove creature position from world area.
                    wArea->RemoveCreaturePosition(targCrea);
                    
// Set player to not target any creature.
                    creaTarg->SetTargetedCreature(nullptr);
                    
// Remove creature from tile.
                    creaTile->SetCreature(nullptr);
                    
                }
            }
        }
    }
    
// Get map of creatures to their coordinates.
    auto &creaCoords = wArea->GetCreaturePositions();
    
// Loop over all creatures with their coordinates.
    for (auto& entry : creaCoords) {
        
// Obtain entry data.
        auto crea = entry.first;
        auto coord = entry.second;
        
// If creature has targeted the current user.
        if (crea->GetTargetedUserID() == userID) {
            
// Calculate absolute distance components.
            auto absDx = std::abs(player->GetCoord().x - coord.x);
            auto absDy = std::abs(player->GetCoord().y - coord.y);
            
// If within melee range.
            if (absDx <= 1 && absDy <= 1) {
                
// When creature is ready to attack.
                if (crea->GetTimerAttackOnOther().Tick(crea->GetAtkSpd())) {
                    
// Determine damage to inflict on player.
                    auto damage = 1;
                    
// Hit player.
                    player->Hit(damage);
              
// If player is dead.      
                    if (player->GetHP() <= 0) {
                     
// Reset character state for by applying start parameters to the player.
                        player->SetCoord({5,5});
                        player->SetDestCoord(std::nullopt);
                        player->SetHP(player->GetMaxHP());
                        player->ResetExp();
                        creaTarg->SetTargetedCreature(nullptr);
                        
// Notify about the player death and penalties applied.
                        textMsgs->Print(
                            "You have died! Your have lost all your experience.");
                    }
                }
            }
        }
    }
}

}