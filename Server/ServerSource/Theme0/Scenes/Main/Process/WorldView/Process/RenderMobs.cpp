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
    
    void RenderMobs(
        const MainScene& mainScene, const UserConnection& userConnection,
        WebSocket &webSocket,
        std::shared_ptr<const Tile> tile, BoxF tileBounds) {
        
        const auto mobTargeting =
            std::static_pointer_cast<MobTargeting>(
                mainScene.m_components.at(
                    MainSceneComponents::
                    MobTargeting));
        
        if (tile->m_mob) {
            
            if (tile->m_mob ==
                mobTargeting->
                m_targetedCreature){
                
                SendImageDrawInstruction(
                    webSocket,
                    "TargetedMob",
                    tileBounds);
            }
            
            SendImageDrawInstruction(
                webSocket,
                tile->m_mob->m_type,
                tileBounds);
            
            SendTextDrawInstruction(
                webSocket,
                "Mob, Lvl." +
                std::to_string(tile->m_mob->m_level),
                {tileBounds.x, tileBounds.y - 0.5f*tileBounds.h});
        }
    }
}