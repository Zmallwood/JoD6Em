/*
 * ImageDrawInstruction.hpp
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
    struct ImageDrawInstruction : public IDrawInstruction {
        
        int imageNameHash {0}; ///<Hash code of image name to draw.
        
        BoxF destination;      ///< Destination rectangle to draw the image at.
    };
}