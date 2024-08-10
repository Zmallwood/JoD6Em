/*
 * MainMenuScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MainMenuScene.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUIButton.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUI.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    
    void MainMenuScene::Initialize(UserID userID) {
        
        GUI()->AddComponent<GUIButton>(BoxF{0.45f, 0.4f, 0.1f, 0.05f}, "Login", [=] {
            
            _<EngineGet>().GetSceneManager(userID)->
            GoToScene(userID, "MainScene");
        });
    }
    
    void MainMenuScene::RenderDerived(UserID userID) const {
        
        auto &webSocket = *_<EngineGet>().GetWebSocket(userID);
        
        SendImageDrawInstruction(
            webSocket, "DefaultSceneBackground",
            {0.0f, 0.0f, 1.0f, 1.0f});
        
        SendImageDrawInstruction(
            webSocket, "JoDLogo",
            {0.4f, 0.1f, 0.2f, 0.1f});
    }
}