/*
 * ObjectHovering.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "IMainSceneComponent.hpp"

namespace JoD {
/// Determines and renders text showing info about hovered objects.
class ObjectHovering : public IMainSceneComponent {
  public:
/// Determine hovered objects and prepare text to draw in render method.
/// @param userID User ID for which this component belongs to.
    void Update(UserID userID) override;
    
/// Draw object hovering text to canvas.
/// @param userID User ID for which this component belongs to.
    void Render(UserID userID) const override;
    
  private:
    std::vector<std::string> m_objectHoverTextLines;
};
}