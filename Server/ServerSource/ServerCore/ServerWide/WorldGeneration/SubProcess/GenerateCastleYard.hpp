/*
 * GenerateCastleYard.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class WorldArea;

///
/// Generates a castle yard with walls in the top left corner of the world area.
///
/// @param worldArea World area to generate a castle yard in.
///
void GenerateCastleYard(WorldArea* worldArea);

}