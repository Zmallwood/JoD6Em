// message_codes.h
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
///////////////////////////////////////////////////////////

#pragma once

namespace jod {
    namespace message_codes {
        constexpr int k_drawImageInstr = 1;
        constexpr int k_applyBuffer = 2;
        constexpr int k_mouseDown = 3;
        constexpr int k_canvasSize = 4;
        constexpr int k_mousePosition = 5;
        constexpr int k_frameFinished = 6;
    }
}