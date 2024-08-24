/*
 * RegisterScene.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RegisterScene.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUI.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUIButton.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUITextBox.hpp"
#include "ServerCore/UserGameInstance/GUICore/GUILabel.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"

namespace JoD {
void RegisterScene::Initialize(UserID userID) {
    GetGUI()->AddComponent<GUILabel>(PointF{0.45f, 0.35f}, "Username");
    GetGUI()->AddComponent<GUITextBox>(BoxF{0.45f, 0.4f, 0.1f, 0.04f});
    
    GetGUI()->AddComponent<GUILabel>(PointF{0.45f, 0.45f}, "Password");
    GetGUI()->AddComponent<GUITextBox>(BoxF{0.45f, 0.5f, 0.1f, 0.04f});
    GetGUI()->AddComponent<GUIButton>(
        BoxF{0.55f, 0.55f, 0.1f, 0.05f}, "Register", [=] {
            _<EngineGet>().GetSceneManager(userID)->
            GoToScene(userID, "MainScene");
        });
    
    GetGUI()->AddComponent<GUIButton>(
        BoxF{0.4f, 0.55f, 0.1f, 0.05f}, "Back", [=] {
            _<EngineGet>().GetSceneManager(userID)->
            GoToScene(userID, "MainMenuScene");
        });
}

void RegisterScene::RenderDerived(UserID userID) const {
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

