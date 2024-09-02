/*
 * TextDrawInstr.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "IDrawInstr.hpp"

namespace JoD {

struct TextDrawInstr : public IDrawInstr {

    PointF position;
    std::string text;
    bool centered {false};
};
}
