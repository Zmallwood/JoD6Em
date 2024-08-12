/*
 * IDrawInstruction.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "DrawInstructionTypes.hpp"

namespace JoD {
    
    ///
    /// Base clase for different kinds of draw instructions.
    ///
    struct IDrawInstruction {
        
        DrawInstructionTypes type {DrawInstructionTypes::None}; ///< Should be specified for all object instances.
        RID rid {0}; ///< Resource ID, used for both image RIDs and text RIDs.
    };
}