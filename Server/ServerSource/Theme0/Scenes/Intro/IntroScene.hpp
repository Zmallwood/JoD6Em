/*
 * IntroScene.hpp
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
    /// @param userID User ID for which the scene belongs to.
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
    /// @param userID User ID for which the scene belongs to.
    ///
    void UpdateDerived(UserID userID) override;
    
    ///
    /// Render the scene to canvas.
    ///
    /// @param userID User ID for which the scene belongs to.
    ///
    void RenderDerived(UserID userID) const override;
    
  private:
    
    // Members
    
    std::shared_ptr<GUILabel>
    m_guiLabelStartText; ///< Show a blinking start text in the center of the canvas.
};

}
