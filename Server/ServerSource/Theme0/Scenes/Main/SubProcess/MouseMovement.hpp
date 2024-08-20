/*
 * MouseMovement.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "IMainSceneComponent.hpp"

namespace JoD {
/// Enables moving the player character by clicking
/// with mouse in the game world.
class MouseMovement : public IMainSceneComponent {
  public:
/// User base ctor.
    using IMainSceneComponent::IMainSceneComponent;
    
/// Override base class method.
/// @param userID User ID for user which the component belongs to.
    void Update(UserID userID) override;
};
}
