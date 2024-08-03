/*
 * mouse_button.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class mouse_button {
    public:
        void register_mouse_down();
        
        bool is_pressed_pick_result();
        
        bool m_is_pressed;
    };
}