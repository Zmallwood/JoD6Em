/*
 * GUIExpBar.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "ServerCore/UserGameInstance/GUICore/GUIComponent.hpp"

namespace JoD {
///  Experience bar located at the bottom of canvas, show experience progress
///  for player.
class GUIExpBar : public GUIComponent {
  public:
/// Construct a new GUIExpBar object.
    GUIExpBar();
    
/// Calculates the filled amount of the experience bar.
/// @param userID User ID for user which the experience bar belongs to.
    void UpdateDerived(UserID userID) override;
    
/// Renders the experience bar to the bottom of canvas.
/// @param userID User ID for user which the experience bar belongs to.
    void RenderDerived(UserID userID) const override;
    
/// Get the height of the experience bar, used by other GUI components
/// to position correctly.
/// @return constexpr float Height of the experience bar.
    static constexpr float GetHeight() {
        return k_height;
    }
    
  private:
// Filled amount of the bar, in the range 0.0f - 1.0f.
    float m_filledAmount {0.0f};             
// Height of the bar.
    static constexpr float k_height {0.03f}; 
};
}
