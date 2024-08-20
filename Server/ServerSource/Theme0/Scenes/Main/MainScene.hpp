/*
 * MainScene.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "ServerCore/UserGameInstance/ScenesCore/IScene.hpp"
#include "SubProcess/MainSceneComponents.hpp"

namespace JoD {
class IMainSceneComponent;

/// The main scene where the playing takes place.
class MainScene : public IScene {
  public:
    /// Construct a new MainScene object.
    MainScene();
    
    /// Destroy the MainScene object. Necessary for PIMPL idiom.
    ~MainScene();
    
    /// Get the a component of the provided type.
    /// @param mainSceneComponent Component type to obtain.
    /// @return IMainSceneComponent* Component that was requested, or nullptr if doesnt exist.
    IMainSceneComponent *GetComponent(
        MainSceneComponents mainSceneComponent) const;
    
  protected:
    /// Adds components to the scene.
    /// @param userID User ID for user which the MainScene belongs to.
    void Initialize(UserID userID) override;
    
    /// Called every time the user enters this scene.
    /// @param userID User ID for user which the MainScene belongs to.
    void OnEnterDerived(UserID userID) override;
    
    /// Update game logic.
    /// @param userID User ID for user which the MainScene belongs to.
    void UpdateDerived(UserID userID) override;
    
    /// Render the scene to canvas.
    /// @param userID User ID for user which the MainScene belongs to.
    void RenderDerived(UserID userID) const override;
    
  private:
// PIMPL idiom.
    struct Impl;
// PIMPL idiom.
    std::unique_ptr<Impl> m_pImpl;
};
}
