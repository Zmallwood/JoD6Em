/*
 * UpdateAnimalsEating.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class Tile;

///
/// Update animals eating grass from the ground they stand on.
///
/// @param tile Tile to update.
///
void UpdateAnimalsEating(Tile* tile);

}