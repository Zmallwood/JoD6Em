/*
 * MainScene.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MainScene.hpp"
#include "SubProcess/TileHovering.hpp"
#include "SubProcess/MouseMovement.hpp"
#include "SubProcess/CreatureTargeting.hpp"
#include "SubProcess/Combat.hpp"
#include "SubProcess/CombatMovement.hpp"
#include "SubProcess/WorldView/WorldView.hpp"
#include "SubProcess/ObjectHovering.hpp"
#include "MainSceneGUI/GUITextConsole.hpp"
#include "MainSceneGUI/GUIExpBar.hpp"
#include "MainSceneGUI/GUIStatusPanel.hpp"
#include "MainSceneGUI/InteractionMenu/GUIInteractionMenu.hpp"
#include "ServerCore/UserGameInstance/TextOutput/TextMessages.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUI.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUIButton.hpp"
#include "SubProcess/IMainSceneComponent.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
struct MainScene::Impl {
// Contains sub components for the scene.
    std::map<MainSceneComponents, std::unique_ptr<IMainSceneComponent>>
    components;
};

MainScene::MainScene() :
    IScene(), m_pImpl(std::make_unique<Impl>()) {}

MainScene::~MainScene() {}

void MainScene::Initialize(UserID userID) {
// Add system GUIButton.
    GetGUI()->AddComponent<GUIButton>(
        BoxF{0.96f, 0.89f, 0.03f,
             0.03f * _<EngineGet>().GetAspectRatio(userID).value()}, "", [=] {},
        "GUIButtonSystem",
        "GUIButtonSystemHovered");
// Add skills GUIButton.
    GetGUI()->AddComponent<GUIButton>(
        BoxF{0.92f, 0.89f, 0.03f,
             0.03f * _<EngineGet>().GetAspectRatio(userID).value()}, "", [=] {},
        "GUIButtonSkills",
        "GUIButtonSkillsHovered");
// Add inventory GUIButton.
    GetGUI()->AddComponent<GUIButton>(
        BoxF{0.88f, 0.89f, 0.03f,
             0.03f * _<EngineGet>().GetAspectRatio(userID).value()}, "", [=] {},
        "GUIButtonInventory",
        "GUIButtonInventoryHovered");
// Add character GUIButton.
    GetGUI()->AddComponent<GUIButton>(
        BoxF{0.84f, 0.89f, 0.03f,
             0.03f * _<EngineGet>().GetAspectRatio(userID).value()}, "", [=] {},
        "GUIButtonCharacter",
        "GUIButtonCharacterHovered");
// Add text console GUI component.
    GetGUI()->AddComponent<GUITextConsole>();
// Add experience bar GUI component.
    GetGUI()->AddComponent<GUIExpBar>();
// Add status panel GUI component.
    GetGUI()->AddComponent<GUIStatusPanel>();
// Add interaction menu GUI component.
    GetGUI()->AddComponent<GUIInteractionMenu>();
// Add tile hovering component.
    m_pImpl->components.insert(
        {MainSceneComponents::TileHovering,
         std::make_unique<TileHovering>() });
// Add mouse movement component.
    m_pImpl->components.insert(
        {MainSceneComponents::MouseMovement,
         std::make_unique<MouseMovement>() });
// Add creature targeting component.
    m_pImpl->components.insert(
        {MainSceneComponents::CreatureTargeting,
         std::make_unique<CreatureTargeting>() });
// Add world view component.
    m_pImpl->components.insert(
        {MainSceneComponents::WorldView,
         std::make_unique<WorldView>() });
// Add combat movement component.
    m_pImpl->components.insert(
        {MainSceneComponents::CombatMovement,
         std::make_unique<CombatMovement>() });
// Add combat component.
    m_pImpl->components.insert(
        {MainSceneComponents::Combat,
         std::make_unique<Combat>() });
// Add object hovering.
    m_pImpl->components.insert(
        {MainSceneComponents::ObjectHovering,
         std::make_unique<ObjectHovering>() });
}

void MainScene::OnEnterDerived(UserID userID) {
// Notify user about entering the game world.
    _<EngineGet>().GetTextMessages(userID)->Print("Entering world.");
}

void MainScene::UpdateDerived(UserID userID) {
// Update all components for the scene.
    for (const auto& component : m_pImpl->components)
        component.second->Update(userID);
}

void MainScene::RenderDerived(UserID userID) const {
// Render all components for the scene.
    for (const auto& component : m_pImpl->components)
        component.second->Render(userID);
}

IMainSceneComponent *MainScene::GetComponent(
    MainSceneComponents mainSceneComponent) const {
// If component of type has been added to the scene.
    if (m_pImpl->components.contains(mainSceneComponent))
// Return it.
        return m_pImpl->components.at(mainSceneComponent).get();
// Component with the type douesnt exists, return fail value.
    return nullptr;
}
}