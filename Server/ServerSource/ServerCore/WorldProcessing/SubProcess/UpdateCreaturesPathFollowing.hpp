/*
 * UpdateCreaturesPathFollowing.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class Tile;

///
/// Update creatures following a road path.
///
/// @param tile Tile object where the creature is located.
/// @param coord Coordinate where the creature is located.
///
void UpdateCreaturesPathFollowing(Tile* tile, Point coord);

}