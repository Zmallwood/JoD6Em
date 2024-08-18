/*
 * GUI.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUI.hpp"

namespace JoD {

void GUI::Update(UserID userID) {
    
// Iterate through all components.
    for (auto& component : m_components) {
        
// And update them.
        component->Update(userID);
    }
}

void GUI::Render(UserID userID) const {
    
// Iterate through all components.
    for (auto& component : m_components) {
        
// And render them.
        component->Render(userID);
    }
}

}