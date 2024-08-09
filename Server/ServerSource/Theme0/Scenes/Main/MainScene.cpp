/*
 * MainScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MainScene.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "Process/TileHovering.hpp"
#include "Process/MouseMovement.hpp"
#include "Process/MobTargeting.hpp"
#include "Process/CombatMovement.hpp"
#include "Process/WorldView/WorldView.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"
#include "Theme0/Scenes/Main/Process/MainSceneComponents.hpp"
#include "MainSceneGUI/GUITextConsole.hpp"
#include "ServerCore/UserGameInstance/TextOutput/TextOut.hpp"

namespace JoD {
    
    void MainScene::Initialize() {
        
        GUI()->AddComponent<GUITextConsole>();
        
        m_components.insert(
            {MainSceneComponents::TileHovering,
             std::make_shared<TileHovering>(
                 this->EngineInstance()) });
                 
        m_components.insert(
            {MainSceneComponents::MouseMovement,
             std::make_shared<MouseMovement>(
                 this->EngineInstance()) });
                 
        m_components.insert(
            {MainSceneComponents::MobTargeting,
             std::make_shared<MobTargeting>(
                 this->EngineInstance()) });
                 
        m_components.insert(
            {MainSceneComponents::WorldView,
             std::make_shared<WorldView>(this->EngineInstance()) });
                 
        m_components.insert(
            {MainSceneComponents::CombatMovement,
             std::make_shared<CombatMovement>(this->EngineInstance()) });
    }
    
    void MainScene::OnEnter() {
        
        EngineInstance().TextOut()->Print("Entering world.");
    }
    
    void MainScene::UpdateDerived(UserID userID) {
        
        for (const auto component : m_components) {
            
            component.second->Update();
        }
    }
    
    void MainScene::RenderDerived(UserID userID, WebSocket &webSocket) const {
        
        for (const auto component : m_components) {
            
            component.second->Render(webSocket);
        }
    }
}