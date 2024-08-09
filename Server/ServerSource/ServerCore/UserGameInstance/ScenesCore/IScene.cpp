/*
 * IScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IScene.hpp"

namespace JoD {
    
    IScene::IScene(JoD::EngineInstance& engineInstance)
        : m_engineInstance(engineInstance),
        m_gui(std::make_unique<JoD::GUI>()) {
        
    }
    
    void IScene::Update(UserID userID) {
        
        m_gui->Update(userID);
        
        UpdateDerived(userID);
    }
    
    void IScene::Render(UserID userID, WebSocket &webSocket) const {
        
        RenderDerived(userID, webSocket);
        
        m_gui->Render(userID, webSocket);
    }
}