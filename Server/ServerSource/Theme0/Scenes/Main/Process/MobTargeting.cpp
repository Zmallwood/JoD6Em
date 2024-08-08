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
#include <optional>

namespace JoD {
    
    void MobTargeting::Update() {
        
        const std::unique_ptr<Player> &player =
            EngineInstance().Player();
        
        const std::shared_ptr<const TileHovering> tileHovering =
            std::static_pointer_cast<TileHovering>(
                EngineInstance().SceneManager()->GetScene<MainScene>("MainScene")->m_components.at(
                    MainSceneComponents::
                    TileHovering));
        
        const auto mouseDown =
            EngineInstance().MouseInput()->
            RightButton()->
            IsPressedPickResult();
        
        const auto hoveredTile =
            tileHovering->m_hoveredCoordinate;
        
        if (mouseDown) {
            
            player->SetDestCoord(std::nullopt);
            
            const auto &worldArea = _<World>().GetCurrentWorldArea();
            
            const auto tile = worldArea->GetTile(hoveredTile);
            
            if (tile->GetMob()) {
                
                m_targetedCreature = tile->GetMob();
                
            }else {
                
                m_targetedCreature = nullptr;
            }
        }
    }
}