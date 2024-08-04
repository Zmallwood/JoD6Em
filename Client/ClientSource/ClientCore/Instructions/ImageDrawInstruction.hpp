/*
 * ImageDrawInstruction.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "InstructionTypes.hpp"

namespace JoD {
    /// @brief Holds data for doing a image drawing operation, created when such a request is
    ///        incoming from the server.
    struct ImageDrawInstruction {
        InstructionTypes type = InstructionTypes::none;

        RID rid = -1; ///< ID for an image resource previously allocated.
        
        int image_name_hash = 0; ///<Hash code of image name to draw.
        
        RectF destination; ///< Destination rectangle to draw the image at.

        PointF position;

        std::string text;
    };
}