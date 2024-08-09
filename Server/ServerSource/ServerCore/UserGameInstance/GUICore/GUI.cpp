/*
 * GUI.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUI.hpp"

namespace JoD {
    void GUI::Update(UserID userID) {
        
        for (auto& component : m_components) {
            
            component->Update(userID);
        }
    }
    
    void GUI::Render(UserID userID, WebSocket &webSocket) const {
        
        
        for (auto& component : m_components) {
            
            component->Render(userID, webSocket);
        }
    }
}