/*
 * CombatMovement.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "IMainSceneComponent.hpp"

namespace JoD {
/// Handles combat moving, such as chasing a targeted creature.
class CombatMovement : public IMainSceneComponent {
  public:
/// User default ctor.
    using IMainSceneComponent::IMainSceneComponent;
    
/// Override base class method.
    void Update(UserID userID) override;
};
}
