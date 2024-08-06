/*
 * TileHovering.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "IMainSceneComponent.hpp"

namespace JoD {
    
    ///
    /// Enables hovering the tile currently under the mouse cursor.
    ///
    class TileHovering : public IMainSceneComponent  {
        
      public:
        ///
        /// Use base ctor.
        ///
        using IMainSceneComponent::IMainSceneComponent;
        
        ///
        /// Override base class methdo.
        ///
        void Update() override;
        
        Point m_hoveredCoordinate {-1, -1}; ///< Currently hovered tile coordinate, {-1, -1} means none.
    };
}