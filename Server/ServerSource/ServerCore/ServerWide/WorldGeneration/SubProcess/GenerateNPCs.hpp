/*
 * GenerateNPCs.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class WorldArea;

///
/// Generate NPCs on the roads in a world area.
///
/// @param worldArea World area to generate NPCs on.
///
void GenerateNPCs(WorldArea* worldArea);

}