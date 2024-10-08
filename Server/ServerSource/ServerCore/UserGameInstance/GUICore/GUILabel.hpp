/*
 * GUILabel.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "GUIComponent.hpp"

namespace JoD {
/// Draws a single string of text to the canvas.
class GUILabel : public GUIComponent {
  public:
/// Construct a new GUILabel object.
/// @param position Position in the canvas.
/// @param text Text to draw.
/// @param centerAligned If position represents text center or text top left corner.
    GUILabel(PointF position, std::string_view text,
             bool centerAligned = false, GUIComponent *parent = nullptr);
    
/// Do the rendering of the label text.
/// @param userID User ID for which user GUI the GUILabel belongs to.
    void RenderDerived(UserID userID) const override;
    
  private:
// Text to draw.
    std::string m_text;
// Text center align state.
    bool m_centerAligned {false};
};
}
