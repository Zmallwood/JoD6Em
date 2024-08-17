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
#include "Theme0/Scenes/Main/SubProcess/MainSceneComponents.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "ObjectsPile.hpp"
#include "Object.hpp"
#include "Theme0/Scenes/Main/SubProcess/TileHovering.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {

GUIInteractionMenu::GUIInteractionMenu()
    : GUIComponent({0.0f, 0.0f}) {}

void GUIInteractionMenu::UpdateDerived(UserID userID) {
    
    auto mouseInput = _<EngineGet>().GetMouseInput(userID);
    
    auto sceneManager = _<EngineGet>().GetSceneManager(userID);
    
    auto mainScene = sceneManager->GetScene<MainScene>("MainScene");
    
    auto tileHovering =
        static_cast<TileHovering*>(mainScene->GetComponent(
                                       MainSceneComponents::TileHovering));
    auto mousePosition = _<EngineGet>().GetMousePosition(userID).value();
    
    if (mouseInput->GetRightButton().GetIsPressed()) {
        
        auto tile =
            _<World>().GetCurrWorldArea()->GetTile(
                tileHovering->GetHoveredCoordinate().value());
        
        m_clickedCoord = tileHovering->GetHoveredCoordinate().value();
        
        if (tile->GetCreature()) {
            
            m_active = false;
            
            return;
        }
        
        
        m_position = mousePosition;
        
        m_active = true;
        
        m_menuEntries.clear();
        
        auto menuEntryIndex = 0;
        
        for (auto object : tile->GetObjectsPile().GetObjects()) {
            
            if (object->GetType() == Hash("ObjectTree1") ||
                object->GetType() == Hash("ObjectTree2")){
                
                m_menuEntries.push_back(
                    {.label="Chop down tree", .action = [&] {
                                                            auto tile =
                                                                _<World>().
                                                                GetCurrWorldArea()
                                                                ->GetTile(
                                                                    m_clickedCoord);
                                                            
                                                            for (auto object
                                                                 : tile->
                                                                 GetObjectsPile()
                                                                 .GetObjects()){
                                                                
                                                                if (object->
                                                                    GetType()
                                                                    == Hash(
                                                                        "ObjectTree1")
                                                                    ||
                                                                    object->
                                                                    GetType()
                                                                    == Hash(
                                                                        "ObjectTree2"))
                                                                {
                                                                    tile->
                                                                    GetObjectsPile()
                                                                    .
                                                                    RemoveObject
                                                                    (
                                                                        object);
                                                                    tile->
                                                                    GetObjectsPile()
                                                                    .
                                                                    AddObject
                                                                    (
                                                                        "ObjectFelledTree");
                                                                    break;
                                                                }
                                                            }
                                                        },
                     .bounds = {m_position.x,
                                m_position.y + menuEntryIndex*k_menuRowHeight,
                                m_size.w, k_menuRowHeight}});
                
                menuEntryIndex++;
            }
        }
    }
    
    if (!m_active) {
        
        return;
    }
    
    if (mouseInput->GetLeftButton().GetIsPressed()) {
        
        for (auto menuEntry: m_menuEntries) {
            
            auto bounds = menuEntry.bounds;
            
            if (bounds.Contains(mousePosition)) {
                
                menuEntry.action();
            }
        }
        
        
        m_active = false;
    }
}

void GUIInteractionMenu::RenderDerived(UserID userID) const {
    
    if (!m_active) {
        
        return;
    }
    
    SendImageDrawInstruction(userID, "GUIPanelBground", GetBounds());
    
    auto linePos = m_position;
    
    for (auto menuEntry : m_menuEntries) {
        
        SendTextDrawInstruction(userID, menuEntry.label, linePos);
        
        linePos.y += k_menuRowHeight;
    }
}

BoxF GUIInteractionMenu::GetBounds() const {
    
    return {m_position.x, m_position.y, m_size.w, m_size.h};
}

}