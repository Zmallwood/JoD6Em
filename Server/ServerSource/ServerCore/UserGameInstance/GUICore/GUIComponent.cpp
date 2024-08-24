/*
 * GUIComponent.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUIComponent.hpp"
#include "GUI.hpp"

namespace JoD {
GUIComponent::GUIComponent(PointF position,
                           GUIComponent *parent)
    : m_position(position), m_parent(parent) {}

void GUIComponent::Update(UserID userID) {
// Call update function of inheriting type.
    UpdateDerived(userID);
}

void GUIComponent::Render(UserID userID) const {
// Dont render if component is invisible.
    if (!m_visible) return;
// Call render function of inheriting type.
    RenderDerived(userID);
}

GUI *GUIComponent::GetRootGUI() const {
    GUIComponent *currParent = GetParent();
    
    while (currParent->GetParent() != nullptr) {
        currParent = currParent->GetParent();
    }
    return static_cast<GUI*>(currParent);
}
}
