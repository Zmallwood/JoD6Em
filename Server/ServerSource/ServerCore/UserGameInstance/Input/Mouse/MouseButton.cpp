/*
 * MouseButton.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseButton.h"

namespace JoD {
    void MouseButton::RegisterMouseDown()      {
        m_is_pressed = true;
    }
    
    bool MouseButton::IsPressedPickResult()      {
        auto result = m_is_pressed;
        m_is_pressed = false;
        return result;
    }
}