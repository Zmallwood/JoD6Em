/*
 * GUIInteractionMenu.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/GUICore/GUIComponent.hpp"
#include "MenuEntry.hpp"

namespace JoD {
/// Menu used to perform actions in the game world, activated by right clicking.
class GUIInteractionMenu : public GUIComponent {
  public:
/// Construct a new GUIInteractionMenu object.
    GUIInteractionMenu(GUIComponent *parent = nullptr);
    
/// Checks if the menu should be activated by populating with menu options,
/// and checks if an option has been clicked to perform its action.
/// @param userID User ID for which the menu belons to.
    void UpdateDerived(UserID userID) override;
    
/// Renders the menu to the canvas.
/// @param userID User ID for which the menu belons to.
    void RenderDerived(UserID userID) const override;
    
  private:
/// Get the Bounds object by combining position and size.
/// @return BoxF Bounds of the menu.
    BoxF GetBounds() const;
    
// Size of the menu in canvas.
    SizeF m_size {0.1f, 0.05f};
// Determines if the menu is visible and clickable.
    bool m_active {false};
// All current entries in the menu.
    std::vector<MenuEntry> m_menuEntries;
// Coordinate of tile clicked for which the menu operates.
    Point m_clickedCoord = {-1, -1};
// Height of one row in the menu in the canvas.
    const float k_menuRowHeight {0.1f};
};
}
