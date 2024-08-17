/*
 * TextDrawInstruction.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "IDrawInstruction.hpp"

namespace JoD {
    
///
/// Holds data for doing a image drawing operation, created when such a request is
/// incoming from the server.
///
struct TextDrawInstruction : public IDrawInstruction {
    
    PointF position;                ///< Position at where the text will be drawn, if its a text render instruction.
    
    std::string text;               ///< Text to draw if its a text render instruction.
    
    bool centerAligned {false};     ///< If the position member specifies the center point or left op corner of the text.
};

}