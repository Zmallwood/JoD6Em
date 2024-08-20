/*
 * TileHovering.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "IMainSceneComponent.hpp"

namespace JoD {
/// Enables hovering the tile currently under the mouse cursor.
class TileHovering : public IMainSceneComponent {
  public:
    /// Use base ctor.
    using IMainSceneComponent::IMainSceneComponent;
    
    /// Override base class method.
    /// @param userID User ID for user which the component belongs.
    void Update(UserID userID) override;
    
    std::optional<Point> GetHoveredCoord() const {
        return m_hoveredCoord;
    }
    
  private:
// Currently hovered tile coordinate, {-1, -1} means none.
    std::optional<Point> m_hoveredCoord {std::nullopt};
};
}
