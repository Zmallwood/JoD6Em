/*
 * MainScene.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/ScenesCore/IScene.hpp"
#include "SubProcess/MainSceneComponents.hpp"

namespace JoD {

class IMainSceneComponent;

///
/// The main scene where the playing takes place.
///
class MainScene : public IScene {
    
  public:
    
    MainScene();
    
    ~MainScene();
    
    IMainSceneComponent *GetComponent(
        MainSceneComponents mainSceneComponent) const;
    
  protected:
    
    ///
    /// Adds components to the scene.
    ///
    void Initialize(UserID userID) override;
    
    void OnEnterDerived(UserID userID) override;
    
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
    
    struct Impl;
    
    std::unique_ptr<Impl> m_pImpl;
};

}
