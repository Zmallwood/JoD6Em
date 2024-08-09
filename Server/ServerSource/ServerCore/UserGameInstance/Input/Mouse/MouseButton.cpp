/*
 * MouseButton.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseButton.hpp"

namespace JoD {
    
    void MouseButton::RegisterMouseDown() {
        
        m_isPressed = true; 
    }
    
    void MouseButton::RegisterMouseUp() {
        
        m_isPressed = false; 
    }
    
    bool MouseButton::IsPressedPickResult() {
        
        const auto result = m_isPressed;
        
        m_isPressed = false;
        
        return result;
    }
}