/*
 * MainScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MainScene.hpp"
#include "SubProcess/TileHovering.hpp"
#include "SubProcess/MouseMovement.hpp"
#include "SubProcess/CreatureTargeting.hpp"
#include "SubProcess/Combat.hpp"
#include "SubProcess/CombatMovement.hpp"
#include "SubProcess/WorldView/WorldView.hpp"
#include "MainSceneGUI/GUITextConsole.hpp"
#include "MainSceneGUI/GUIExpBar.hpp"
#include "MainSceneGUI/GUIStatusPanel.hpp"
#include "MainSceneGUI/InteractionMenu/GUIInteractionMenu.hpp"
#include "ServerCore/UserGameInstance/TextOutput/TextMessages.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUI.hpp"
#include "SubProcess/IMainSceneComponent.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {

struct MainScene::Impl {
    std::map<MainSceneComponents, std::unique_ptr<IMainSceneComponent>>
    components;     ///< Contains sub components for the scene.
};

MainScene::MainScene() :
    IScene(), m_pImpl(std::make_unique<Impl>()) {}

MainScene::~MainScene() {}

void MainScene::Initialize(UserID userID) {
    
    GetGUI()->AddComponent<GUITextConsole>();
    
    GetGUI()->AddComponent<GUIExpBar>();
    
    GetGUI()->AddComponent<GUIStatusPanel>();
    
    GetGUI()->AddComponent<GUIInteractionMenu>();
    
    m_pImpl->components.insert(
        {MainSceneComponents::TileHovering,
         std::make_unique<TileHovering>() });
    
    m_pImpl->components.insert(
        {MainSceneComponents::MouseMovement,
         std::make_unique<MouseMovement>() });
    
    m_pImpl->components.insert(
        {MainSceneComponents::CreatureTargeting,
         std::make_unique<CreatureTargeting>() });
    
    m_pImpl->components.insert(
        {MainSceneComponents::WorldView,
         std::make_unique<WorldView>() });
    
    m_pImpl->components.insert(
        {MainSceneComponents::CombatMovement,
         std::make_unique<CombatMovement>() });
    
    m_pImpl->components.insert(
        {MainSceneComponents::Combat,
         std::make_unique<Combat>() });
}

void MainScene::OnEnter(UserID userID) {
    
    std::cout << "User " << userID << " entered MainScene\n";
    
    _<EngineGet>().GetTextMessages(userID)->Print("Entering world.");
}

void MainScene::UpdateDerived(UserID userID) {
    
    for (const auto& component : m_pImpl->components) {
        
        component.second->Update(userID);
    }
}

void MainScene::RenderDerived(UserID userID) const {
    
    for (const auto& component : m_pImpl->components) {
        
        component.second->Render(userID);
    }
}

IMainSceneComponent *MainScene::GetComponent(
    MainSceneComponents mainSceneComponent) const {
    
    if (m_pImpl->components.contains(mainSceneComponent)) {
        
        return m_pImpl->components.at(mainSceneComponent).get();
    }
    
    return nullptr;
}

}