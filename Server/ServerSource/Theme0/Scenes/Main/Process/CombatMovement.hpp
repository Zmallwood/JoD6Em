/*
 * CombatMovement.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "IMainSceneComponent.hpp"

namespace JoD {
    class CombatMovement : public IMainSceneComponent {
      public:
        using IMainSceneComponent::IMainSceneComponent;
        
        void Update() override;
    };
}