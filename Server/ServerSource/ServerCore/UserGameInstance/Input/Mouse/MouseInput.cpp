/*
 * MouseInput.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseInput.hpp"
#include "MouseButton.hpp"

namespace JoD {
    MouseInput::MouseInput() : m_left_button(
            std::make_shared<MouseButton>()),
        m_right_button(std::make_shared<MouseButton>()){
    }
    
    void MouseInput::RegisterMouseDown(MouseButtons button) {
        switch (button) {
        case MouseButtons::left:
            m_left_button->RegisterMouseDown();
            break;
        case MouseButtons::right:
            m_right_button->RegisterMouseDown();
            break;
        case MouseButtons::none:
            break;
        }
    }
}