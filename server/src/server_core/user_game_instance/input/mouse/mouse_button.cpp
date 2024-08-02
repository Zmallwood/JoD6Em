/*
 * mouse_button.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "mouse_button.h"

namespace jod {
    void
    mouse_button::register_mouse_down(){
        m_isPressed = true;
    }
    
    bool
    mouse_button::is_pressed_pick_result(){
        auto result = m_isPressed;
        m_isPressed = false;
        return result;
    }
}