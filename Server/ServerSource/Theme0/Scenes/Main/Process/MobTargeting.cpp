/*
 * MobTargeting.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MobTargeting.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"
#include "TileHovering.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"

namespace JoD {
    
    void MobTargeting::Update(UserID userID) {
        
        auto player =
            EngineInstance().Player();
        
        auto tileHovering =
            static_cast<TileHovering*>(
                EngineInstance().SceneManager()->GetScene<MainScene>("MainScene")->GetComponent(
                    MainSceneComponents::
                    TileHovering));
        
        const auto mouseDown =
            EngineInstance().MouseInput()->
            RightButton().
            IsPressedPickResult();
        
        const auto hoveredTile =
            tileHovering->HoveredCoordinate();
        
        if (mouseDown && hoveredTile.has_value()) {
            
            player->SetDestCoord(std::nullopt);
            
            const auto &worldArea = _<World>().GetCurrentWorldArea();
            
            const auto &tile = worldArea->GetTile(hoveredTile.value());
            
            if (tile->GetMob()) {
                
                m_targetedCreature = tile->GetMob();
                
            }else {
                
                m_targetedCreature = nullptr;
            }
        }
    }
}