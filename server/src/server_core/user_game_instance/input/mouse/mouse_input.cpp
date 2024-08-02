/*
 * mouse_input.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "mouse_input.h"
#include "mouse_button.h"

namespace jod {   
    mouse_input::mouse_input() : m_left_button(std::make_shared<mouse_button>()){
    }
    
    void
    mouse_input::register_mouse_down(){
        m_left_button->register_mouse_down();
    }
}