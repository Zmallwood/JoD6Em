/*
 * CursorTypes.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Available cursor types, which should hint what kind of
/// effect a mouse click would have.
///
enum class CursorTypes {
    
    Default,     ///< Default when clicking has no unusual effect.
    Hovering     ///< Hints that mouse is hovering a clickable button.
};

}