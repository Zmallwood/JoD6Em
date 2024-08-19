/*
 * UpdateObjects.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class Tile;

///
/// Update objects on a specific tile.
/// 
/// @param tile Tile containin the objects to update.
///
void UpdateObjects(Tile* tile);

}