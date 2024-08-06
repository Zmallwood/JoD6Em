/*
 * MouseInput.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "MouseButtons.hpp"

namespace JoD {
    
    class MouseButton;
    
    ///
    /// Manages mouse input for a single user.
    ///
    class MouseInput {
        
      public:
        ///
        /// Construct a new Mouse Input object by initializing
        /// left and right mouse buttons.
        ///
        MouseInput();
        
        ///
        /// Registers one of the mouse buttons as having been pressed down.
        ///
        /// @param button Which button, left or right.
        ///
        void RegisterMouseDown(MouseButtons button);
        
        std::shared_ptr<MouseButton> m_leftButton; ///< Left mouse button.
        std::shared_ptr<MouseButton> m_rightButton; ///< Right mouse button.
    };
}