/*
 * ImageDrawInstr.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "IDrawInstr.hpp"

namespace JoD {

struct ImageDrawInstr : public IDrawInstr {
    
    int imgNameHash {0};
    BoxF dest {0.0f, 0.0f};
    bool repeatTex {false};
    SizeF texFillAmount {1.0f, 1.0f};
};
}
