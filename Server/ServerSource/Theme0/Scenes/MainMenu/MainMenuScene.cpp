/*
 * MainMenuScene.cpp
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
// Add Login GUIButton.
    GetGUI()->AddComponent<GUIButton>(
        BoxF{0.45f, 0.4f, 0.1f, 0.05f}, "Login", [=] {
// On click: go to MainScene.
            _<EngineGet>().GetSceneManager(userID)->
            GoToScene(userID, "MainScene");
        });
// Add Register GUIButton.
    GetGUI()->AddComponent<GUIButton>(
        BoxF{0.45f, 0.46f, 0.1f, 0.05f}, "Register", [=] {});
}

void MainMenuScene::RenderDerived(UserID userID) const {
// Draw default scene background image.
    UserSendDrawImage(
        userID, "DefaultSceneBackground",
        {0.0f, 0.0f, 1.0f, 1.0f});
// Draw Journey of Dreams logo image.
    UserSendDrawImage(
        userID, "JoDLogo",
        {0.4f, 0.1f, 0.2f, 0.1f});
}
}