/*
 * GenerateElevation.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
class WorldArea;

/// Generate elevation on a world area.
/// @param worldArea World area to generate elevation on.
void GenerateElevation(WorldArea* worldArea);
}