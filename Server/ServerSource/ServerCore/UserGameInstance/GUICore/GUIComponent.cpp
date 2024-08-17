/*
 * GUIComponent.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUIComponent.hpp"

namespace JoD {

GUIComponent::GUIComponent(PointF position)
    : m_position(position) {}

void GUIComponent::Update(UserID userID) {
    
    // Call update function of inheriting type.
    UpdateDerived(userID);
}

void GUIComponent::Render(UserID userID) const {
    
    // Dont render if component is invisible.
    if (!m_visible) {
        
        return;
    }
    
    // Call render function of inheriting type.
    RenderDerived(userID);
}

}