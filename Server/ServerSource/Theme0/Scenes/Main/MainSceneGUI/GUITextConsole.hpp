/*
 * GUITextConsole.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "ServerCore/UserGameInstance/GUICore/GUIPanel.hpp"

namespace JoD {
/// Text console GUI component at bottom left of the canvas.
class GUITextConsole : public GUIPanel {
  public:
    /// Construct a new GUITextConsole object.
    GUITextConsole();
    
    /// Render the text console to canvas.
    /// @param userID User ID for user which the text console belongs to.
    void RenderDerived(UserID userID) const override;
    
  private:
// Width of the text console.
    static constexpr float k_width {0.35f};
// Height of the text console.
    static constexpr float k_height {0.2f};
// Line height in the text console.
    static constexpr float k_lineHeight {0.02f};
// Margin inside the edges of the text console.
    static constexpr float k_margin {0.005f};
};
}
