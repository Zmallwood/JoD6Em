/*
 * RenderNPCs.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class Tile;

void RenderNPCs(UserID userID, Tile* tile, BoxF tileBounds);

}