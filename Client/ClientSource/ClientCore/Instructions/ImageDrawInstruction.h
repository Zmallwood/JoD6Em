/*
 * ImageDrawInstruction.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "InstructionTypes.h"

namespace jod {
    //! \brief Holds data for doing a image drawing operation, created when such a request is
    //!        incoming from the server.
    struct image_draw_instruction {
        instruction_types type = instruction_types::none;

        rid rid = -1; //!< ID for an image resource previously allocated.
        
        int image_name_hash = 0; //!<Hash code of image name to draw.
        
        rectf destination; //!< Destination rectangle to draw the image at.

        pointf position;

        std::string text;
    };
}