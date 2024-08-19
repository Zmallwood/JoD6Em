/*
 * GenerateHorseCarts.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class WorldArea;

///
/// Generate horses with dragged carts on the roads in a world area.
///
/// @param worldArea World area to generate horse carts on.
///
void GenerateHorseCarts(WorldArea* worldArea);

}