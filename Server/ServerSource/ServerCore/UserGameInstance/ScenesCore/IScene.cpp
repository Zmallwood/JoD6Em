/*
 * IScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IScene.hpp"

namespace JoD {
    IScene::IScene(UserConnection& userConnection)
        : m_userConnection(userConnection) {
    }
    
    void IScene::Update() {
        UpdateDerived();
    }
    
    void IScene::Render(WebSocket &webSocket) const {
        RenderDerived(webSocket);
    }
}