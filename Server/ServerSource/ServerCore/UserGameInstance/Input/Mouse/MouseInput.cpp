/*
 * MouseInput.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseInput.hpp"
#include "MouseButton.hpp"

namespace JoD {
    
    struct MouseInput::Impl {
        std::unique_ptr<MouseButton> leftButton; ///< Left mouse button.
        std::unique_ptr<MouseButton> rightButton; ///< Right mouse button.
    };
    
    MouseInput::MouseInput() : m_pImpl(std::make_unique<Impl>()) {
        
        m_pImpl->leftButton = std::make_unique<MouseButton>();
        m_pImpl->rightButton = std::make_unique<MouseButton>();
    }
    
    MouseInput::~MouseInput() {
        
    }
    
    void MouseInput::RegisterMouseDown(MouseButtons button) {
        
        switch (button) {
        
        case MouseButtons::Left: {
            
            m_pImpl->leftButton->RegisterMouseDown();
            
            break;
        }
        case MouseButtons::Right: {
            
            m_pImpl->rightButton->RegisterMouseDown();
            
            break;
        }
        case MouseButtons::None: {
            
            break;
        }
        }
    }
    
    void MouseInput::RegisterMouseUp(MouseButtons button) {
        
        switch (button) {
        
        case MouseButtons::Left: {
            
            m_pImpl->leftButton->RegisterMouseUp();
            
            break;
        }
        case MouseButtons::Right: {
            
            m_pImpl->rightButton->RegisterMouseUp();
            
            break;
        }
        case MouseButtons::None: {
            
            break;
        }
        }
    }
    
    MouseButton &MouseInput::GetLeftButton() const {
        
        return *m_pImpl->leftButton;
    }
    
    MouseButton &MouseInput::GetRightButton() const {
        
        return *m_pImpl->rightButton;
    }
}