/*
 * mouse_input.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "mouse_input.h"
#include "mouse_button.h"

namespace jod {   
    mouse_input::mouse_input() : m_leftButton(std::make_shared<mouse_button>()){
    }
    
    void
    mouse_input::register_mouse_down(){
        m_leftButton->register_mouse_down();
    }
    

}