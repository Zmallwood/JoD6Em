/*
 * GUIComponent.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUIComponent.hpp"

namespace JoD {
    GUIComponent::GUIComponent(PointF position)
    : m_position(position) {
        
    }
    
    void GUIComponent::Update(UserID userID) {
        
        UpdateDerived(userID);
    }
    
    void GUIComponent::Render(UserID userID, WebSocket &webSocket) const {
        
        if (!m_visible) {
            
            return;
        }
        
        RenderDerived(userID, webSocket);
    }
}