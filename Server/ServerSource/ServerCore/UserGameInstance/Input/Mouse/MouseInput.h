/*
 * MouseInput.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "MouseButtons.h"

namespace JoD {
    class MouseButton;

    class MouseInput {
    public:
        MouseInput();
        
        void RegisterMouseDown(MouseButtons button);
        
        std::shared_ptr<MouseButton> m_left_button;
        std::shared_ptr<MouseButton> m_right_button;
    };
}