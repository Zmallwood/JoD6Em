/*
 * IScene.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IScene.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUI.hpp"

namespace JoD {

struct IScene::Impl {
    
    std::unique_ptr<JoD::GUI> gui; // A single GUI for every scene.
    
    bool initialized {false};
};

IScene::IScene()
    : m_pImpl(std::make_unique<Impl>()) {
    
// Create the scenes GUI object.
    m_pImpl->gui = std::make_unique<JoD::GUI>();
}

IScene::~IScene() {}

void IScene::OnEnter(UserID userID) {
    
    if (!m_pImpl->initialized) {
        
        Initialize(userID);
    }
    
    OnEnterDerived(userID);
}

void IScene::Update(UserID userID) {
    
// Update GUI.
    m_pImpl->gui->Update(userID);

// Update everything else.
    UpdateDerived(userID);
}

void IScene::Render(UserID userID) const {
    
// Render everything except GUI.
    RenderDerived(userID);
    
// Render GUI.
    m_pImpl->gui->Render(userID);
}

GUI* IScene::GetGUI() const {
    
// Return raw pointer to GUI.
    return m_pImpl->gui.get();
}

}