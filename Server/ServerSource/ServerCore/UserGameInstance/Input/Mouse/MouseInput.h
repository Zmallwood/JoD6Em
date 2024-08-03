/*
 * MouseInput.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "MouseButtons.h"

namespace jod {
    class mouse_button;

    class mouse_input {
    public:
        mouse_input();
        
        void register_mouse_down(mouse_buttons button);
        
        std::shared_ptr<mouse_button> m_left_button;
        std::shared_ptr<mouse_button> m_right_button;
    };
}