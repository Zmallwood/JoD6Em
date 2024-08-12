/*
 * IDrawInstruction.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "DrawInstructionTypes.hpp"

namespace JoD {
    
    struct IDrawInstruction {
        
        DrawInstructionTypes type {DrawInstructionTypes::None};
        RID rid {0};
    };
}