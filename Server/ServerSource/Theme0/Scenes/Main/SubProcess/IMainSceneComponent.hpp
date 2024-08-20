/*
 * IMainSceneComponent.h
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
class EngineInstance;

/// Base class for all components contained in MainScene.
class IMainSceneComponent {
    
  public:
/// Optionally overridable for inheriting component classes.
/// @param userID User ID for which the updated component belongs to.
    virtual void Update(UserID userID) {}
    
/// Optionally overridable for inheriting component classes.
/// @param userID User ID for which the rendered component belongs to.
    virtual void Render(UserID userID) const {}
};
}