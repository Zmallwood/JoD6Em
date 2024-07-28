// Copyright (c) 2024 Andreas Åkerberg.

#include "WorldGeneration.h"

#include "World.h"

namespace jod
{
  void GenerateNewWorld()
  {
    auto worldArea = _<World>().m_currentWorldArea;

    for (auto y = 0; y < 100; y++)
    {
        for (auto x = 0; x < 100; x++)
        {
            worldArea->m_tiles[x][y]->m_ground = Hash("GroundWater");
        }
    }
  }
}