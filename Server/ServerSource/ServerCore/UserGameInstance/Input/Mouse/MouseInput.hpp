/*
 * MouseInput.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "MouseButtons.hpp"

namespace JoD {
    class MouseButton;
    
    class MouseInput {
      public:
        MouseInput();
        
        void RegisterMouseDown(MouseButtons button);
        
        std::shared_ptr<MouseButton> m_leftButton;
        std::shared_ptr<MouseButton> m_rightButton;
    };
}