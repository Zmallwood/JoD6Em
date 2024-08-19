/*
 * CreatureTargeting.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "CreatureTargeting.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "TileHovering.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {

void CreatureTargeting::Update(UserID userID) {
    
    auto player =
        _<EngineGet>().GetPlayer(userID);
    
    auto tileHovering =
        static_cast<TileHovering*>(
            _<EngineGet>().GetSceneManager(userID)->GetScene<MainScene>(
                "MainScene")->GetComponent(
                MainSceneComponents::
                TileHovering));
    
    const auto mouseDown =
        _<EngineGet>().GetMouseInput(userID)->
        GetRightButton().
        GetIsPressedPickResult();
    
    const auto hoveredTile =
        tileHovering->GetHoveredCoord();
    
    if (mouseDown && hoveredTile.has_value()) {
        
        player->SetDestCoord(std::nullopt);
        
        const auto &worldArea = _<World>().GetCurrWorldArea();
        
        const auto &tile = worldArea->GetTile(hoveredTile.value());
        
        if (tile->GetCreature()) {
            
            m_targetedCreature = tile->GetCreature();
            
        }
        else {
            
            m_targetedCreature = nullptr;
        }
    }
}

}