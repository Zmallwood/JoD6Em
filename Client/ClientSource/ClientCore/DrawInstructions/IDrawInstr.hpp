/*
 * IDrawInstr.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "DrawInstrTypes.hpp"

namespace JoD {

struct IDrawInstr {
    
    DrawInstrTypes type {DrawInstrTypes::None};
    RID rid {0};
};
}
