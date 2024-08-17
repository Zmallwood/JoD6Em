/*
 * MouseButton.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseButton.hpp"

namespace JoD {

void MouseButton::RegisterMouseDown() {
    
    // Set pressed state accordingly.
    m_isPressed = true;
}

void MouseButton::RegisterMouseUp() {
    
    // Set pressed state accordingly.
    m_isPressed = false;
}

bool MouseButton::GetIsPressedPickResult() {
    
    // Save state.
    const auto result = m_isPressed;
    
    // Reset state.
    m_isPressed = false;
    
    // Return saved state.
    return result;
}

}