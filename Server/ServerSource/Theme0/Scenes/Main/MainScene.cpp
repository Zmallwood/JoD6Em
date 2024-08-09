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
#include "ServerCore/UserGameInstance/TextOutput/TextMessages.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUI.hpp"
#include "Process/IMainSceneComponent.hpp"

namespace JoD {
    
    struct MainScene::Impl {
        std::map<MainSceneComponents, std::unique_ptr<IMainSceneComponent>>
        components; ///< Contains sub components for the scene.
    };
    
    MainScene::MainScene(JoD::EngineInstance& engineInstance):
    IScene(engineInstance), m_pImpl(std::make_unique<Impl>()) {
        
    }
    
    MainScene::~MainScene() {
        
    }
    
    void MainScene::Initialize() {
        
        GUI()->AddComponent<GUITextConsole>();
        
        m_pImpl->components.insert(
            {MainSceneComponents::TileHovering,
             std::make_unique<TileHovering>(
                 this->EngineInstance()) });
                 
        m_pImpl->components.insert(
            {MainSceneComponents::MouseMovement,
             std::make_unique<MouseMovement>(
                 this->EngineInstance()) });
                 
        m_pImpl->components.insert(
            {MainSceneComponents::MobTargeting,
             std::make_unique<MobTargeting>(
                 this->EngineInstance()) });
                 
        m_pImpl->components.insert(
            {MainSceneComponents::WorldView,
             std::make_unique<WorldView>(this->EngineInstance()) });
                 
        m_pImpl->components.insert(
            {MainSceneComponents::CombatMovement,
             std::make_unique<CombatMovement>(this->EngineInstance()) });
    }
    
    void MainScene::OnEnter() {
        
        EngineInstance().TextOut()->Print("Entering world.");
    }
    
    void MainScene::UpdateDerived(UserID userID) {
        
        for (const auto& component : m_pImpl->components) {
            
            component.second->Update(userID);
        }
    }
    
    void MainScene::RenderDerived(UserID userID, WebSocket &webSocket) const {
        
        for (const auto& component : m_pImpl->components) {
            
            component.second->Render(userID, webSocket);
        }
    }
    
    IMainSceneComponent *MainScene::GetComponent(MainSceneComponents mainSceneComponent) const {
        
        if (m_pImpl->components.contains(mainSceneComponent)) {
            
            return m_pImpl->components.at(mainSceneComponent).get();
        }
        
        return nullptr;
    }
}