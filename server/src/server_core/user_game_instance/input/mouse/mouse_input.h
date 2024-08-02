/*
 * mouse_input.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class mouse_button;

    class mouse_input {
    public:
        mouse_input();
        
        void register_mouse_down();
        
        std::shared_ptr<mouse_button> m_leftButton;
    };
}