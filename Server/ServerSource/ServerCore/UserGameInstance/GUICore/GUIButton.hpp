/*
 * GUIButton.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "GUIComponent.hpp"

namespace JoD {

///
/// A clickable button with a text label in the GUI.
///
class GUIButton : public GUIComponent {
    
  public:
    
    //////
    /// Construct a new GUIButton object
    ///
    /// @param bounds
    /// @param text
    /// @param action
    ///
    ///
    /// @param bounds Area in which the button will be rendered and is clickable.
    /// @param text Label text to draw on top of the button image.
    /// @param action Action to perform when the button is clicked.
    ///
    GUIButton(BoxF bounds, std::string_view text,
              std::function<void()> action,
              std::string_view imageNameDefault = "GUIButtonBground",
              std::string_view imageNameHovered = "GUIButtonHoveredBground");
    
    ///
    /// Update hovered status and check if button has been clicked.
    ///
    /// @param userID User ID for which user GUI the button belongs to.
    ///
    void UpdateDerived(UserID userID) override;
    
    ///
    /// Render the buttons image and text label.
    ///
    /// @param userID User ID for which user GUI the button belongs to.
    ///
    void RenderDerived(UserID userID) const override;
    
  private:
    
    ///
    /// Get the bounds of the GUI button.
    ///
    /// @return BoxF GUI button bounds.
    ///
    BoxF GetBounds() const;
    
    // Members
    
    std::string m_text;                                             ///< Text label that is drawn on top of button image.
    
    SizeF m_size;                                                   ///< Size of button.
    
    std::function<void()> m_action;                                 ///< Action to be performed when the button is clicked.
    
    bool m_hovered {false};                                         ///< Holds the hovered state of the button.
    
    std::string m_imageNameDefault;            ///< Image to draw when button is not hovered.
    
    std::string m_imageNameHovered;     ///< Image to draw when button is hovered.
};

}
