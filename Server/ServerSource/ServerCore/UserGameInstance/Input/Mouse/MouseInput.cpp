/*
 * MouseInput.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseInput.hpp"
#include "MouseButton.hpp"

namespace JoD {
    
    MouseInput::MouseInput() : m_leftButton(
            std::make_shared<MouseButton>()),
        m_rightButton(std::make_shared<MouseButton>()){
        
    }
    
    void MouseInput::RegisterMouseDown(MouseButtons button) {
        
        switch (button) {
        
        case MouseButtons::Left: {
            
            m_leftButton->RegisterMouseDown();
            break;
        }
        case MouseButtons::Right: {
            
            m_rightButton->RegisterMouseDown();
            break;
        }
        case MouseButtons::None: {
            
            break;
        }
        }
    }
}