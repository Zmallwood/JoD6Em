/*
 * IScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IScene.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUI.hpp"

namespace JoD {
    
    struct IScene::Impl {
        JoD::EngineInstance *engineInstance; ///< User connection object for current user.
        std::unique_ptr<JoD::GUI> gui;
    };
    
    IScene::IScene(JoD::EngineInstance& engineInstance)
        : m_pImpl(std::make_unique<Impl>()) {
        
        m_pImpl->engineInstance = &engineInstance;
        m_pImpl->gui = std::make_unique<JoD::GUI>();
    }
    
    IScene::~IScene() {
        
    }
    
    void IScene::Update(UserID userID) {
        
        m_pImpl->gui->Update(userID);
        
        UpdateDerived(userID);
    }
    
    void IScene::Render(UserID userID, WebSocket &webSocket) const {
        
        RenderDerived(userID, webSocket);
        
        m_pImpl->gui->Render(userID, webSocket);
    }

    JoD::EngineInstance& IScene::EngineInstance() const {
        
        return *m_pImpl->engineInstance;
    }
    
    const std::unique_ptr<JoD::GUI>& IScene::GUI() const {
        
        return m_pImpl->gui;
    }
}