/*
 * GUIInteractionMenu.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUIInteractionMenu.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "Theme0/Scenes/Main/Process/MainSceneComponents.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Theme0/Scenes/Main/Process/TileHovering.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    GUIInteractionMenu::GUIInteractionMenu()
        : GUIComponent({0.0f, 0.0f})  {
        
    }
    
    void GUIInteractionMenu::UpdateDerived(UserID userID) {
        
        auto mouseInput = _<EngineGet>().GetMouseInput(userID);
        
        auto sceneManager = _<EngineGet>().GetSceneManager(userID);
        
        auto mainScene = sceneManager->GetScene<MainScene>("MainScene");
        
        auto tileHovering = static_cast<TileHovering*>(mainScene->GetComponent(MainSceneComponents::TileHovering));
        
        if (mouseInput->GetRightButton().GetIsPressed()) {
            
            auto tile = _<World>().GetCurrentWorldArea()->GetTile(tileHovering->GetHoveredCoordinate().value());
            
            if (tile->GetCreature()) {
                
                return;
            }
            
            auto mousePosition = _<EngineGet>().GetMousePosition(userID).value();
            
            m_position = mousePosition;
            
            m_active = true;
        }
        
        if (!m_active) {
            
            return;
        }
        
        if (mouseInput->GetLeftButton().GetIsPressed()) {
            
            m_active = false;
        }
    }
    
    void GUIInteractionMenu::RenderDerived(UserID userID) const {
        
        if (!m_active) {
            
            return;
        }
        
        SendImageDrawInstruction(userID, "GUIPanelBground", GetBounds());
    }
    
    BoxF GUIInteractionMenu::GetBounds() const {
        
        return {m_position.x, m_position.y, m_size.w, m_size.h};
    }
}