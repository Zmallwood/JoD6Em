/*
 * GUIStatusPanel.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "ServerCore/UserGameInstance/GUICore/GUIPanel.hpp"

namespace JoD {
/// A GUI component on canvas which shows basic information about the player.
class GUIStatusPanel : public GUIPanel {
  public:
/// Construct a new GUIStatusPanel object
    GUIStatusPanel(GUIComponent *parent = nullptr);
    
/// Render the panel in the top left corner of the canvas.
/// @param userID User ID for which user the panel belongs to.
    void RenderDerived(UserID userID) const override;
    
  private:
// Width of the panel.
    static constexpr float k_width {0.15f};
// Height of the panel.
    static constexpr float k_height {0.12f};
};
}
