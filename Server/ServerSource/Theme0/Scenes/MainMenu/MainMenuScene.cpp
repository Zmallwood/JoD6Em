/*
 * MainMenuScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MainMenuScene.h"
#include "ServerCore/Net/UserConnection.h"
#include "ServerCore/UserGameInstance/ServerEngine.h"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.h"

namespace jod {
    void MainMenuScene::UpdateDerived() {
        if (m_user_connection.m_server_engine->m_mouse_input->m_left_button->
            is_pressed_pick_result()) {
            m_user_connection.m_server_engine->m_scene_manager->go_to(
                "MainScene");
        }
    }
    
    void MainMenuScene::RenderDerived(WebSocket &webSocket) {
        m_user_connection.send_image_draw_instruction(
            webSocket, "DefaultSceneBackground",
            {0.0f, 0.0f, 1.0f, 1.0f});
        m_user_connection.send_image_draw_instruction(
            webSocket, "JoDLogo",
            {0.4f, 0.1f, 0.2f, 0.1f});
    }
}