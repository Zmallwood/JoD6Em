/*
 * IScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IScene.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUI.hpp"

namespace JoD {
    
    struct IScene::Impl {
        std::unique_ptr<JoD::GUI> gui;
    };
    
    IScene::IScene()
        : m_pImpl(std::make_unique<Impl>()) {
        
        m_pImpl->gui = std::make_unique<JoD::GUI>();
    }
    
    IScene::~IScene() {
        
    }
    
    void IScene::Update(UserID userID) {
        
        m_pImpl->gui->Update(userID);
        
        UpdateDerived(userID);
    }
    
    void IScene::Render(UserID userID) const {
        
        RenderDerived(userID);
        
        m_pImpl->gui->Render(userID);
    }
    
    const std::unique_ptr<JoD::GUI>& IScene::GUI() const {
        
        return m_pImpl->gui;
    }
}