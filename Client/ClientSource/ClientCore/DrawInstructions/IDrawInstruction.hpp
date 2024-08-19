/*
 * IDrawInstruction.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "DrawInstructionTypes.hpp"

namespace JoD {
/// Base clase for different kinds of draw instructions.
struct IDrawInstruction {
    /// Should be specified for all object instances.
    DrawInstructionTypes type {DrawInstructionTypes::None};
    /// Resource ID, used for both image RIDs and text RIDs.
    RID rid {0};    
};
}