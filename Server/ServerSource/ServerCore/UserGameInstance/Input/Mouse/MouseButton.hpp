/*
 * MouseButton.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
/// A single button object, of which two are created for each user,
/// left and right.
class MouseButton {
  public:
/// Register the button has been pressed down.
    void RegisterMouseDown();
    
/// Register the button has been released.
    void RegisterMouseUp();
    
/// Get the buttons pressed state and resets it at the same time.
/// @return true Button is currently being pressed down.
/// @return false Button is currently not being pressed down.
    bool GetIsPressedPickResult();
    
/// Get the pressed state for the button.
/// @return true If button is currently pressed down.
/// @return false If button is not currently pressed down.
    bool GetIsPressed() const {
        return m_isPressed;
    }
    
  private:
// Pressed down state.
    bool m_isPressed {false};
};
}
