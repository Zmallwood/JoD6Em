/*
 * MouseButton.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class MouseButton {
    public:
        void RegisterMouseDown();
        
        bool IsPressedPickResult();
        
        bool m_is_pressed;
    };
}