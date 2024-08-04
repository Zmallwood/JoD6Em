/*
 * WorldView.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "Theme0/Scenes/Main/Process/IMainSceneComponent.hpp"

namespace JoD {
    class WorldView : public IMainSceneComponent {
      public:
        using IMainSceneComponent::IMainSceneComponent;
        
        void Render(WebSocket &webSocket) const override;
    };
}