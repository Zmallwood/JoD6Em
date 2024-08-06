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

namespace JoD {
    
    void RenderMobs(
        MainScene& mainScene, UserConnection& userConnection,
        WebSocket &webSocket,
        std::shared_ptr<Tile> tile, BoxF tileBounds) {
        
        auto mobTargeting =
            std::static_pointer_cast<MobTargeting>(
                mainScene.m_components.at(
                    MainSceneComponents::
                    MobTargeting));
        
        if (tile->m_mob) {
            
            if (tile->m_mob ==
                mobTargeting->
                m_targetedCreature){
                
                userConnection.SendImageDrawInstruction(
                    webSocket,
                    "TargetedMob",
                    tileBounds);
            }
            
            userConnection.SendImageDrawInstruction(
                webSocket,
                tile->m_mob->m_type,
                tileBounds);
            
            userConnection.SendTextDrawInstruction(
                webSocket,
                "Mob, Lvl." +
                std::to_string(tile->m_mob->m_level),
                {tileBounds.x, tileBounds.y - 0.5f*tileBounds.h});
        }
    }
}