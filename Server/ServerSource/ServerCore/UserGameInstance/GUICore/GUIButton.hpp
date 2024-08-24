/*
 * GUIButton.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "GUIComponent.hpp"

namespace JoD {
/// A clickable button with a text label in the GUI.
class GUIButton : public GUIComponent {
  public:
/// Construct a new GUIButton object
/// @param bounds Area in which the button will be rendered and is clickable.
/// @param text Label text to draw on top of the button image.
/// @param action Action to perform when the button is clicked.
/// @param imageNameDefault Image name when button is not hovered.
/// @param imageNameHovered Image name when button is hovered.
    GUIButton(BoxF bounds, std::string_view text,
              std::function<void()> action,
              std::string_view imageNameDefault,
              std::string_view imageNameHovered,
              GUIComponent *parent = nullptr);
    
    GUIButton(BoxF bounds, std::string_view text, std::function<void()> action,
              GUIComponent *parent = nullptr);
    
/// Update hovered status and check if button has been clicked.
/// @param userID User ID for which user GUI the button belongs to.
    void UpdateDerived(UserID userID) override;
    
/// Render the buttons image and text label.
/// @param userID User ID for which user GUI the button belongs to.
    void RenderDerived(UserID userID) const override;
    
  private:
/// Get the bounds of the GUI button.
/// @return BoxF GUI button bounds.
    BoxF GetBounds() const;
    
// Text label that is drawn on top of button image.
    std::string m_text;
// Size of button.
    SizeF m_size;
// Action to be performed when the button is clicked.
    std::function<void()> m_action;
// Holds the hovered state of the button.
    bool m_hovered {false};
// Image to draw when button is not hovered.
    std::string m_imageNameDefault = "GUIButtonBground";
// Image to draw when button is hovered.
    std::string m_imageNameHovered = "GUIButtonHoveredBground";
};
}
