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
#include "Theme0/Scenes/Main/Process/MainSceneComponents.hpp"

namespace JoD {
    
    void MainScene::Initialize() {
        
        m_components.insert(
            {MainSceneComponents::TileHovering,
             std::make_shared<TileHovering>(
                 m_userConnection, *this) });
                 
        m_components.insert(
            {MainSceneComponents::MouseMovement,
             std::make_shared<MouseMovement>(
                 m_userConnection, *this) });
                 
        m_components.insert(
            {MainSceneComponents::MobTargeting,
             std::make_shared<MobTargeting>(
                 m_userConnection, *this) });
                 
        m_components.insert(
            {MainSceneComponents::WorldView,
             std::make_shared<WorldView>(m_userConnection, *this) });
                 
        m_components.insert(
            {MainSceneComponents::CombatMovement,
             std::make_shared<CombatMovement>(m_userConnection, *this) });
    }
    
    void MainScene::UpdateDerived() {
        
        for (const auto component : m_components) {
            
            component.second->Update();
        }
    }
    
    void MainScene::RenderDerived(WebSocket &webSocket) const {
        
        for (const auto component : m_components) {
            
            component.second->Render(webSocket);
        }
    }
}