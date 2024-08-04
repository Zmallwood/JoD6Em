/*
 * IntroScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IntroScene.h"
#include "ServerCore/Net/UserConnection.h"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.h"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.h"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.h"

namespace jod {
    void IntroScene::UpdateDerived() {
        if (m_user_connection.m_user_game_instance_engine->m_mouse_input->
            m_left_button->
            is_pressed_pick_result()) {
            m_user_connection.m_user_game_instance_engine->m_scene_manager->
            go_to(
                "MainMenuScene");
        }
    }
    
    void IntroScene::RenderDerived(WebSocket
                                   &webSocket) {
        m_user_connection.send_image_draw_instruction(
            webSocket, "DefaultSceneBackground",
            {0.0f, 0.0f, 1.0f, 1.0f});
        m_user_connection.send_image_draw_instruction(
            webSocket, "JoDLogo",
            {0.3f, 0.2f, 0.4f, 0.2f});
    }
}