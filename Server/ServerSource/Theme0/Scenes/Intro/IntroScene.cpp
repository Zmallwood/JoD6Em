/*
 * IntroScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IntroScene.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUILabel.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUI.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    
    void IntroScene::Initialize(UserID userID) {
        
        m_guiLabelStartText = GUI()->AddComponent<GUILabel>(PointF{0.5f, 0.5f}, "Press to start", true);
    }
    
    void IntroScene::UpdateDerived(UserID userID) {
        
        if (_<EngineGet>().GetMouseInput(userID)->
            GetLeftButton().
            GetIsPressedPickResult()) {
            
            _<EngineGet>().GetSceneManager(userID)->
            GoToScene(userID, "MainMenuScene");
        }
        
        auto now = Now();
        
        auto showStartText = (now.time_since_epoch().count() % 2000000)/1000000;
        
        m_guiLabelStartText->SetVisible(showStartText);
    }
    
    void IntroScene::RenderDerived(UserID userID) const {
        
        auto &webSocket = *_<EngineGet>().GetWebSocket(userID);
        
        SendImageDrawInstruction(
            webSocket, "DefaultSceneBackground",
            {0.0f, 0.0f, 1.0f, 1.0f});
        
        SendImageDrawInstruction(
            webSocket, "JoDLogo",
            {0.3f, 0.2f, 0.4f, 0.2f});
    }
}