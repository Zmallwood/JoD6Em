/*
 * Combat.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "IMainSceneComponent.hpp"

namespace JoD {
/// Updates combat between players and creatures.
class Combat : public IMainSceneComponent {
  public:
    using IMainSceneComponent::IMainSceneComponent;
    
/// Update combat.
/// @param userID User ID for user which the combat is updated for.
    void Update(UserID userID) override;
};
}
