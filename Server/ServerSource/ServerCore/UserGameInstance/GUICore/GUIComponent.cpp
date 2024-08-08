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
    
    void GUIComponent::Update() {
        
        UpdateDerived();
    }
    
    void GUIComponent::Render(WebSocket &webSocket) {
        
        if (!m_visible) {
            
            return;
        }
        
        RenderDerived(webSocket);
    }
}