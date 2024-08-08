/*
 * MainMenuScene.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MainMenuScene.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    void MainMenuScene::UpdateDerived() {
        
        if (EngineInstance().MouseInput()->
            LeftButton()->
            IsPressedPickResult()) {
            
            EngineInstance().SceneManager()->
            GoToScene("MainScene");
        }
    }
    
    void MainMenuScene::RenderDerived(WebSocket &webSocket) const {
        
        SendImageDrawInstruction(
            webSocket, "DefaultSceneBackground",
            {0.0f, 0.0f, 1.0f, 1.0f});
        
        SendImageDrawInstruction(
            webSocket, "JoDLogo",
            {0.4f, 0.1f, 0.2f, 0.1f});
    }
}