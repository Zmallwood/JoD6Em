/*
 * MainMenuScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MainMenuScene.h"
#include "ServerCore/Net/UserConnection.h"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.h"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.h"

namespace JoD {
    void MainMenuScene::UpdateDerived() {
        if (m_user_connection.m_user_game_instance_engine->m_mouse_input->
            m_left_button->
            IsPressedPickResult()) {
            m_user_connection.m_user_game_instance_engine->m_scene_manager->
            GoTo("MainScene");
        }
    }
    
    void MainMenuScene::RenderDerived(WebSocket &webSocket) {
        m_user_connection.SendImageDrawInstruction(
            webSocket, "DefaultSceneBackground",
            {0.0f, 0.0f, 1.0f, 1.0f});
        m_user_connection.SendImageDrawInstruction(
            webSocket, "JoDLogo",
            {0.4f, 0.1f, 0.2f, 0.1f});
    }
}