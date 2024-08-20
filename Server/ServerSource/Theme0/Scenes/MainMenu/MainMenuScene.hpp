/*
 * MainMenuScene.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "ServerCore/UserGameInstance/ScenesCore/IScene.hpp"

namespace JoD {
/// The main menu scene which is entered after the intro scene.
class MainMenuScene : public IScene {
  public:
/// Use base class ctor.
    using IScene::IScene;
    
/// Initialize the scene by adding GUI components.
/// @param userID User ID for user which the MainMenuScene belongs to.
    void Initialize(UserID userID) override;
    
  protected:
/// Render the scene to canvas.
/// @param userID User ID for user which the MainMenuScene belongs to.
    void RenderDerived(UserID userID) const override;
};
}
