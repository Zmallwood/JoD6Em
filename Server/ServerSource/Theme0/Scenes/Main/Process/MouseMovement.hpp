/*
 * MouseMovement.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "IMainSceneComponent.hpp"

namespace JoD {
    class MouseMovement : public IMainSceneComponent  {
    public:
        using IMainSceneComponent::IMainSceneComponent;
        
        MouseMovement(UserConnection &user_connection);
        
        void Update() override;
    };
}