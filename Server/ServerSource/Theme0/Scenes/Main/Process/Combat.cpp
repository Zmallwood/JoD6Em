/*
 * Combat.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Combat.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "MobTargeting.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/Object.hpp"
#include "ServerCore/ServerWide/WorldStructure/Mob.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"

namespace JoD {

    void Combat::Update(UserID userID) {
        
        auto player =
            _<EngineGet>().GetPlayer(userID);
        
        auto mobTargeting =
            static_cast<MobTargeting*>(
                _<EngineGet>().GetSceneManager(userID)->GetScene<MainScene>("MainScene")->GetComponent(
                    MainSceneComponents::
                    MobTargeting));
        
        if (mobTargeting->GetTargetedCreature()) {
            
            const auto &worldArea = _<World>().GetCurrentWorldArea();
            const auto pos =
                worldArea->GetMobCoord(mobTargeting->GetTargetedCreature()).value();
            
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
                    
                    mobTargeting->GetTargetedCreature()->Hit(1);
                    
                    worldArea->GetTile(pos)->SetGroundCover(Hash("GroundCoverPoolOfBlood"));
                    
                    if (mobTargeting->GetTargetedCreature()->GetHP() <= 0) {
                        
                        worldArea->GetTile(pos)->SetObject(std::make_unique<Object>("ObjectBoneRemains"));
                        
                        player->AddExperience(mobTargeting->GetTargetedCreature()->GetExp());
                        
                        worldArea->RemoveMobPosition(mobTargeting->GetTargetedCreature());
                        
                        mobTargeting->SetTargetedCreature(nullptr);
                        
                        worldArea->GetTile(pos)->SetMob(nullptr);
                        
                    }
                }
            }
        }
    }
}