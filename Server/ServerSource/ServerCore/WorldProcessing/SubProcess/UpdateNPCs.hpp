/*
 * UpdateNPCs.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class Tile;

///
/// Update NPCs.
/// 
/// @param tile Tile containing the NPC to update.
/// @param coord Coordinate where the tile with the NPC is located.
///
void UpdateNPCs(Tile* tile, Point coord);

}