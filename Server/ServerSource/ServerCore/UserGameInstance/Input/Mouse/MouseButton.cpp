/*
 * MouseButton.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseButton.h"

namespace jod {
    void
    mouse_button::register_mouse_down(){
        m_is_pressed = true;
    }
    
    bool
    mouse_button::is_pressed_pick_result(){
        auto result = m_is_pressed;
        m_is_pressed = false;
        return result;
    }
}