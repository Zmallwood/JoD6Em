/*
 * DrawInstruction.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "DrawInstructionTypes.hpp"

namespace JoD {
    
    ///
    /// Holds data for doing a image drawing operation, created when such a request is
    /// incoming from the server.
    ///
    struct DrawInstruction {
        
        DrawInstructionTypes type {DrawInstructionTypes::None}; ///< Type of instruction, such as draw unage or draw text.
        RID rid {0}; ///< ID for an image resource previously allocated.
        int imageNameHash {0}; ///<Hash code of image name to draw.
        BoxF destination; ///< Destination rectangle to draw the image at.
        PointF position; ///< Position at where the text will be drawn, if its a text render instruction.
        std::string text; ///< Text to draw if its a text render instruction.
        bool centerAligned {false};
    };
}