/*
 * GUI.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUI.hpp"

namespace JoD {
    void GUI::Update() {
        
        for (auto& component : m_components) {
            
            component->Update();
        }
    }
    
    void GUI::Render(WebSocket &webSocket) const {
        
        
        for (auto& component : m_components) {
            
            component->Render(webSocket);
        }
    }
}