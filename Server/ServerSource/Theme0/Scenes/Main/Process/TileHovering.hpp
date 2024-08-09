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
        void Update(UserID userID) override;
        
        std::optional<Point> HoveredCoordinate() const {
            
            return m_hoveredCoordinate;
        }
        
      private:
        std::optional<Point> m_hoveredCoordinate {std::nullopt}; ///< Currently hovered tile coordinate, {-1, -1} means none.
    };
}