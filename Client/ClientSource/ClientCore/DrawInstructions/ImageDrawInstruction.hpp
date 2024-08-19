/*
 * ImageDrawInstruction.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "IDrawInstruction.hpp"

namespace JoD {
/// Holds data for doing a image drawing operation, created when such a request is
/// incoming from the server.
///
struct ImageDrawInstruction : public IDrawInstruction {
    /// Hash code of image name to draw.
    int imageNameHash {0};
    /// Destination rectangle to draw the image at.
    BoxF destination;
    /// If texture should be repeated or not.
    bool repeatTexture;
    /// Scale of the texture repetition.
    SizeF textureFillAmount;
};
}