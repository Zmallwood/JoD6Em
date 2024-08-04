/*
 * MainScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MainScene.h"
#include "ServerCore/Net/UserConnection.h"
#include "Process/TileHovering.h"
#include "Process/MouseMovement.h"
#include "Process/MobTargeting.h"
#include "Process/WorldView/WorldView.h"

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