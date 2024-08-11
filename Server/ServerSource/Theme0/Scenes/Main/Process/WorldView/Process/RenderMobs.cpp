/*
 * RenderMobs.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderMobs.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/Creature.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "Theme0/Scenes/Main/Process/CreatureTargeting.hpp"
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
            static_cast<CreatureTargeting*>(
                mainScene.GetComponent(
                    MainSceneComponents::
                    MobTargeting));
        
        if (tile->GetCreature()) {
            
            if (tile->GetCreature() ==
                mobTargeting->
                GetTargetedCreature()){
                
                SendImageDrawInstruction(
                    webSocket,
                    "TargetedMob",
                    tileBounds);
            }
            
            SendImageDrawInstruction(
                webSocket,
                tile->GetCreature()->GetType(),
                tileBounds);
            
            SendTextDrawInstruction(
                webSocket,
                "Mob, Lvl." +
                std::to_string(tile->GetCreature()->GetLevel()),
                {tileBounds.x, tileBounds.y - 0.5f*tileBounds.h});
            
            
            if (Now() < tile->GetCreature()->GetTicksLastHitFromOther() + Duration(
                    Millis(
                        static_cast<int>(
                            k_showHitEffectDuration)))) {
                
                SendImageDrawInstruction(
                    webSocket,
                    "HitEffect",
                    tileBounds);
            }
        }
    }
}