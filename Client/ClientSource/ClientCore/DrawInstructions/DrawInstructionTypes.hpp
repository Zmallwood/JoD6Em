/*
 * DrawInstructionTypes.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Types of instructions that can be recieved from the server.
///
enum class DrawInstructionTypes {
    
    None,          ///< No instruction.
    DrawImage,     ///< Draw an image to the canvas.
    DrawText       ///< Draw text to the canvas.
};

}