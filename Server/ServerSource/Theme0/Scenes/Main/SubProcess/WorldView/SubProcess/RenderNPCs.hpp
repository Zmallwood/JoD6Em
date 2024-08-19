/*
 * RenderNPCs.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class Tile;

///
/// Draw NPC of a tile, if there exists one.
/// 
/// @param userID User ID for user which we draw the NPC for.
/// @param tile Tile which can contain the NPC that will be drawn.
/// @param tileBounds Bounds of the tile which can contain the NPC
///                   that will be drawn.
///
void RenderNPCs(UserID userID, Tile* tile, BoxF tileBounds);

}