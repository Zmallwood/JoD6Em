/*
 * MobTargeting.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MobTargeting.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "TileHovering.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    
    void MobTargeting::Update(UserID userID) {
        
        auto player =
            _<EngineGet>().GetPlayer(userID);
        
        auto tileHovering =
            static_cast<TileHovering*>(
                _<EngineGet>().GetSceneManager(userID)->GetScene<MainScene>("MainScene")->GetComponent(
                    MainSceneComponents::
                    TileHovering));
        
        const auto mouseDown =
            _<EngineGet>().GetMouseInput(userID)->
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