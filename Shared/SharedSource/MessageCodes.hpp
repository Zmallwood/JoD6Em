/*
 * MessageCodes.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    namespace MessageCodes {
        
        constexpr int k_drawImageInstr {1};
        
        constexpr int k_applyBuffer {2};
        
        constexpr int k_leftMouseDown {3};
        
        constexpr int k_canvasSize {4};
        
        constexpr int k_mousePosition {5};
        
        constexpr int k_frameFinished {6};
        
        constexpr int k_drawStringInstr {7};
        
        constexpr int k_rightMouseDown {8};
    }
}