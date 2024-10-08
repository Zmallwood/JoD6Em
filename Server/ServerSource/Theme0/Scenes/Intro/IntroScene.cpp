/*
 * IntroScene.cpp
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
// Add GUILabel for showin blinking start text in center of canvas.
    m_guiLabelStartText = GetGUI()->AddComponent<GUILabel>(
        PointF{0.5f, 0.5f},
        "Press to start", true);
}

void IntroScene::UpdateDerived(UserID userID) {
// Go to MainMenuScene on mouse click.
    if (_<EngineGet>().GetMouseInput(userID)->
        GetLeftButton().
        GetIsPressedPickResult()) {
        _<EngineGet>().GetSceneManager(userID)->
        GoToScene(userID, "MainMenuScene");
    }
// Make start text blink.
    auto showStartText = (Now().time_since_epoch().count() % 2000000)/1000000;
    m_guiLabelStartText->SetVisible(showStartText);
}

void IntroScene::RenderDerived(UserID userID) const {
// Draw scene background image.
    UserSendDrawImage(
        userID, "DefaultSceneBackground",
        {0.0f, 0.0f, 1.0f, 1.0f});
// Draw Journey of Dreams logo image.
    UserSendDrawImage(
        userID, "JoDLogo",
        {0.3f, 0.2f, 0.4f, 0.2f});
}
}