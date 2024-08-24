/*
 * Box.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
/// A box shape of integer type.
struct Box {
/// X coordinate.
    int x {0};
/// Y coordinate.
    int y {0};
/// Width.
    int w {0};
/// Height.
    int h {0};
};
}
