/*
 * RenderCreatures.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderCreatures.hpp"
#include "Tile.hpp"
#include "Creature.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "Theme0/Scenes/Main/SubProcess/CreatureTargeting.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
namespace {
const int k_showHitEffectDuration {300};
}

void RenderCreatures(
    UserID userID,
    Tile* tile, BoxF tileBounds) {
// Get main scene.
    auto mainScene = _<EngineGet>().GetMainScene(userID);
// Access mob targeting component.
    auto mobTargeting = static_cast<CreatureTargeting*>(
        mainScene->GetComponent(
            MainSceneComponents::CreatureTargeting));
    auto creature = tile->GetCreature();
// If creature exists on tile.
    if (creature) {
// If the creature is targeted.
        if (creature == mobTargeting->GetTargetedCreature())
// Draw targeted symbol on tile.
            UserSendDrawImage(userID, "TargetedMob", tileBounds);
// Draw the actual creature.
        UserSendDrawImage(userID, creature->GetType(), tileBounds);
// Draw creature name and level above the creature.
        UserSendDrawText(
            userID,
            "Mob, Lvl." +
            std::to_string(creature->GetLevel()),
            {tileBounds.x, tileBounds.y - 0.5f*tileBounds.h});
// Check if creature has recently been attacked and should have a
// hit effect drawn onto it.
        if (Now() < creature->GetTimeLastHitFromOther() + Duration(
                Millis(
                    static_cast<int>(
                        k_showHitEffectDuration)))) {
            UserSendDrawImage(userID, "HitEffect", tileBounds);
        }
    }
}
}