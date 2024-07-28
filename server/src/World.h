// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
  class WorldArea;
  class Tile;

  class World
  {
   public:
    World();

    std::shared_ptr<WorldArea> m_currentWorldArea;
  };

  class WorldArea
  {
   public:
    WorldArea();

    std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
  };

  class Tile
  {
   public:
    int m_ground = 0;
    int m_object = 0;
  };
}