/*
 * MainScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MainScene.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "Process/TileHovering.hpp"
#include "Process/MouseMovement.hpp"
#include "Process/MobTargeting.hpp"
#include "Process/WorldView/WorldView.hpp"

namespace JoD {
    void MainScene::UpdateDerived() {
        m_user_connection.m_tile_hovering->Update();
        m_user_connection.m_mouse_movement->Update();
        m_user_connection.m_mob_targeting->Update();
    }
    
    void MainScene::RenderDerived(WebSocket &webSocket) {
        m_user_connection.m_worldView->Render(webSocket);
    }
}