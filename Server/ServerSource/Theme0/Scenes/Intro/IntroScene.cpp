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
        
        if (m_userConnection.m_userGameInstanceEngine->m_mouseInput->
            m_leftButton->
            IsPressedPickResult()) {
            m_userConnection.m_userGameInstanceEngine->m_sceneManager->
            GoTo("MainMenuScene");
        }
    }
    
    void IntroScene::RenderDerived(WebSocket
                                   &webSocket) const {
        
        m_userConnection.SendImageDrawInstruction(
            webSocket, "DefaultSceneBackground",
            {0.0f, 0.0f, 1.0f, 1.0f});
        m_userConnection.SendImageDrawInstruction(
            webSocket, "JoDLogo",
            {0.3f, 0.2f, 0.4f, 0.2f});
    }
}