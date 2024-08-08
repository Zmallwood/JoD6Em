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
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUILabel.hpp"

namespace JoD {
    
    void IntroScene::Initialize() {
        
        m_guiLabelStartText = m_gui->AddComponent<GUILabel>(PointF{0.5f, 0.5f}, "Press to start");
    }
    
    void IntroScene::UpdateDerived() {
        
        if (m_userConnection.m_userGameInstanceEngine->m_mouseInput->
            m_leftButton->
            IsPressedPickResult()) {
            
            m_userConnection.m_userGameInstanceEngine->m_sceneManager->
            GoToScene("MainMenuScene");
        }
        
        auto now = Now();
        
        auto showStartText = (now.time_since_epoch().count() % 2000000)/1000000;
        
        m_guiLabelStartText->SetVisible(showStartText);
    }
    
    void IntroScene::RenderDerived(WebSocket
                                   &webSocket) const {
        
        SendImageDrawInstruction(
            webSocket, "DefaultSceneBackground",
            {0.0f, 0.0f, 1.0f, 1.0f});
        
        SendImageDrawInstruction(
            webSocket, "JoDLogo",
            {0.3f, 0.2f, 0.4f, 0.2f});
    }
}