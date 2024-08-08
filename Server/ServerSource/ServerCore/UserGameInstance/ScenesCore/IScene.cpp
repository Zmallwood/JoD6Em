/*
 * IScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IScene.hpp"

namespace JoD {
    
    IScene::IScene(UserGameInstanceEngine& userGameInstanceEngine)
        : m_userGameInstanceEngine(userGameInstanceEngine),
        m_gui(std::make_unique<GUI>()) {
        
    }
    
    void IScene::Update() {
        
        m_gui->Update();
        
        UpdateDerived();
    }
    
    void IScene::Render(WebSocket &webSocket) const {
        
        RenderDerived(webSocket);
        
        m_gui->Render(webSocket);
    }
}