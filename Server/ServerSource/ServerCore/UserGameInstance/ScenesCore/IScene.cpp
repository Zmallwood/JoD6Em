/*
 * IScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IScene.hpp"

namespace JoD {
    IScene::IScene(UserConnection& user_connection)
        : m_user_connection(user_connection) {
    }
    
    void IScene::Update() {
        UpdateDerived();
    }
    
    void IScene::Render(WebSocket &webSocket){
        RenderDerived(webSocket);
    }
}