/*
 * MouseInput.hpp
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
    /// Construct a new MouseInput object by initializing
    /// left and right mouse buttons.
    ///
    MouseInput();
    
    ///
    /// Destroy the MouseInput object, necessary for PIMPL idiom.
    ///
    ~MouseInput();
    
    ///
    /// Registers one of the mouse buttons as having been pressed down.
    ///
    /// @param button Which button, left or right.
    ///
    void RegisterMouseDown(MouseButtons button);
    
    ///
    /// Registers one of the mouse buttons as having been released.
    ///
    /// @param button Which butotn, left or right.
    ///
    void RegisterMouseUp(MouseButtons button);
    
    ///
    /// Get the left button object.
    ///
    /// @return MouseButton& Left mouse button.
    ///
    MouseButton &GetLeftButton() const;
    
    ///
    /// Get the right button object.
    ///
    /// @return MouseButton& Right mouse button.
    ///
    MouseButton &GetRightButton() const;
    
  private:
    
    ///
    /// PIMPL idiom to reduce header includes.
    ///
    struct Impl;
    
    std::unique_ptr<Impl> m_pImpl;
};

}
