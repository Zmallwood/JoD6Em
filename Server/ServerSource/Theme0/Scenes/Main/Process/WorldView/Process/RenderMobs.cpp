/*
 * RenderMobs.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderMobs.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/Mob.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "Theme0/Scenes/Main/Process/MobTargeting.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    namespace {
        
        const int k_showHitEffectDuration {300};
    }
    
    void RenderMobs(
        const MainScene& mainScene,
        WebSocket &webSocket,
        Tile* tile, BoxF tileBounds) {
        
        const auto mobTargeting =
            static_cast<MobTargeting*>(
                mainScene.GetComponent(
                    MainSceneComponents::
                    MobTargeting));
        
        if (tile->GetMob()) {
            
            if (tile->GetMob() ==
                mobTargeting->
                TargetedCreature()){
                
                SendImageDrawInstruction(
                    webSocket,
                    "TargetedMob",
                    tileBounds);
            }
            
            SendImageDrawInstruction(
                webSocket,
                tile->GetMob()->GetType(),
                tileBounds);
            
            SendTextDrawInstruction(
                webSocket,
                "Mob, Lvl." +
                std::to_string(tile->GetMob()->GetLevel()),
                {tileBounds.x, tileBounds.y - 0.5f*tileBounds.h});
            
            
            if (Now() < tile->GetMob()->GetTicksLastHitFromOther() + Duration(
                    Millis(
                        static_cast<int>(
                            1000/
                            k_showHitEffectDuration)))) {
                
                SendImageDrawInstruction(
                    webSocket,
                    "HitEffect",
                    tileBounds);
            }
        }
    }
}