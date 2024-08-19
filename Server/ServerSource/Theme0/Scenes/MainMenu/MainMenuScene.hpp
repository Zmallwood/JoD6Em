/*
 * MainMenuScene.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/ScenesCore/IScene.hpp"

namespace JoD {

///
/// The main menu scene which is entered after the intro scene.
///
class MainMenuScene : public IScene {
    
  public:
    
    ///
    /// Use base class ctor.
    ///
    using IScene::IScene;
    
    void Initialize(UserID userID) override;
    
  protected:
    
    ///
    /// Render the scene to canvas.
    ///
    /// @param webSocket Web socket object for user.
    ///
    void RenderDerived(UserID userID) const override;
};

}
