/*
 * RenderCreatures.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderCreatures.hpp"
#include "Tile.hpp"
#include "Creature.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "Theme0/Scenes/Main/SubProcess/CreatureTargeting.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    namespace {
        
        const int k_showHitEffectDuration {300};
    }
    
    void RenderCreatures(
        const MainScene& mainScene,
        UserID userID,
        Tile* tile, BoxF tileBounds) {
        
        const auto mobTargeting =
            static_cast<CreatureTargeting*>(
                mainScene.GetComponent(
                    MainSceneComponents::
                    CreatureTargeting));
        
        if (tile->GetCreature()) {
            
            if (tile->GetCreature() ==
                mobTargeting->
                GetTargetedCreature()){
                
                SendImageDrawInstruction(
                    userID,
                    "TargetedMob",
                    tileBounds);
            }
            
            SendImageDrawInstruction(
                userID,
                tile->GetCreature()->GetType(),
                tileBounds);
            
            SendTextDrawInstruction(
                userID,
                "Mob, Lvl." +
                std::to_string(tile->GetCreature()->GetLevel()),
                {tileBounds.x, tileBounds.y - 0.5f*tileBounds.h});
            
            
            if (Now() < tile->GetCreature()->GetTimeLastHitFromOther() + Duration(
                    Millis(
                        static_cast<int>(
                            k_showHitEffectDuration)))) {
                
                SendImageDrawInstruction(
                    userID,
                    "HitEffect",
                    tileBounds);
            }
        }
    }
}