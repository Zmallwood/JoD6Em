/*
 * MouseButton.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// A single button object, of which two are created for each user,
    /// left and right.
    ///
    class MouseButton {
        
      public:
        ///
        /// Regoster the buttons has been pressed down.
        ///
        void RegisterMouseDown();
        
        ///
        /// Get the buttons pressed state and resets it at the same time.
        /// 
        /// @return true Button is currently being pressed down.
        /// @return false Button is currently not being pressed down.
        ///
        bool IsPressedPickResult();
        
        bool m_isPressed {false}; ///< Pressed down state.
    };
}