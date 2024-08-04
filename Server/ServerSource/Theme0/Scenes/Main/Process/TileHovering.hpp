/*
 * TileHovering.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "IMainSceneComponent.hpp"

namespace JoD {
    class TileHovering : public IMainSceneComponent  {
    public:
        using IMainSceneComponent::IMainSceneComponent;
        
        void Update() override;
        
        Point m_hovered_coordinate = {-1, -1};
    };
}