/*
 * MenuEntry.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// One clickable entry in the GUIInteractionMenu.
///
struct MenuEntry {
    
    std::string label;                 ///< Text shown for the entry in the menu.
    
    std::function<void(Point)> action; ///< Aciton performed when clicking the menu entry.
    
    BoxF bounds;                       ///< Bounds of the entry on the menu.
};

}
