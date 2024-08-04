/*
 * GenerateNewWorld.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateNewWorld.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "Process/ClearWithGrass.hpp"
#include "Process/GenerateMobs.hpp"
#include "Process/GenerateObjects.hpp"
#include "Process/GenerateWater.hpp"
#include "Process/GenerateRoads.hpp"

namespace JoD {
    void GenerateNewWorld() {
        auto world_area = _<World>().m_current_world_area;
        ClearWithGrass(world_area);
        GenerateWater(world_area);
        GenerateRoads(world_area);
        GenerateObjects(world_area);
        GenerateMobs(world_area);
    }
}