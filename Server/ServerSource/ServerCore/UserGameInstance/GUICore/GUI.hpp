/*
 * GUI.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "GUIComponent.hpp"

namespace JoD {
class GUITextBox;

/// A complete GUI of which every Scene has an instance of.
class GUI : public GUIComponent {
  public:
    GUI();
    
/// Update the whole GUI and all its components.
/// @param userID User ID for which user the GUI belongs to.
    void Update(UserID userID);
    
/// Render the whole GUI and all its components.
/// @param userID User ID for which user the GUI belongs to.
    void Render(UserID userID);
    
/// Add a new component to the GUI.
/// @tparam T Type of component to add.
/// @tparam Args Pack expansion type.
/// @param args Arguments passed on to constructor of component type T.
/// @return std::shared_ptr<T> Newly created and added GUI component.
    template<class T, class ... Args>
    std::shared_ptr<T> AddComponent(Args... args) {
        // Create new component object.
        auto newComponent = std::make_shared<T>(args ..., this);
        // Add it to GUI.
        GetChildComponents().push_back(newComponent);
        // And also return it.
        return newComponent;
    }
    
  private:
    std::shared_ptr<GUITextBox> m_focusedTextBox;
};
}
