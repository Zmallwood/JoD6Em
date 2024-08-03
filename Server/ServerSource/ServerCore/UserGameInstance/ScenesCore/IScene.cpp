/*
 * IScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IScene.h"

namespace jod {
    IScene::IScene(user_connection& user_connection)
        : m_user_connection(user_connection) {
    }
    
    void IScene::Update() {
        UpdateDerived();
    }
    
    void IScene::Render(WebSocket &webSocket)
    {
        RenderDerived(webSocket);
    }
}