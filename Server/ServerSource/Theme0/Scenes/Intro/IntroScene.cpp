/*
 * IntroScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IntroScene.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"

namespace JoD {
    void IntroScene::UpdateDerived() {
        if (m_user_connection.m_user_game_instance_engine->m_mouse_input->
            m_left_button->
            IsPressedPickResult()) {
            m_user_connection.m_user_game_instance_engine->m_scene_manager->
            GoTo("MainMenuScene");
        }
    }
    
    void IntroScene::RenderDerived(WebSocket
                                   &webSocket) {
        m_user_connection.SendImageDrawInstruction(
            webSocket, "DefaultSceneBackground",
            {0.0f, 0.0f, 1.0f, 1.0f});
        m_user_connection.SendImageDrawInstruction(
            webSocket, "JoDLogo",
            {0.3f, 0.2f, 0.4f, 0.2f});
    }
}