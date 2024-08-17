/*
 * IntroScene.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/ScenesCore/IScene.hpp"

namespace JoD {

class GUILabel;

///
/// The first scene presented to the user on game start.
///
class IntroScene : public IScene {
    
  public:
    ///
    /// Adds GUI components and components to the scene.
    ///
    void Initialize(UserID userID) override;
    
    ///
    /// Use base class ctor.
    ///
    using IScene::IScene;
    
  protected:
    ///
    /// Update game logic.
    ///
    void UpdateDerived(UserID userID) override;
    
    ///
    /// Render the scene to canvas.
    ///
    /// @param webSocket Web socket object for user.
    ///
    void RenderDerived(UserID userID) const override;
    
  private:
    
    // Members
    
    std::shared_ptr<GUILabel> m_guiLabelStartText;
};

}
