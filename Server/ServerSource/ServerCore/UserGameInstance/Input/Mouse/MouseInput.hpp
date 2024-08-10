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
        
        ~MouseInput();
        
        ///
        /// Registers one of the mouse buttons as having been pressed down.
        ///
        /// @param button Which button, left or right.
        ///
        void RegisterMouseDown(MouseButtons button);
        
        void RegisterMouseUp(MouseButtons button);
        
        MouseButton &GetLeftButton() const;
        
        MouseButton &GetRightButton() const;
        
      private:
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}