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
        
        const auto& worldArea = _<World>().GetCurrentWorldArea();
        
        ClearWithGrass(worldArea);
        GenerateWater(worldArea);
        GenerateRoads(worldArea);
        GenerateObjects(worldArea);
        GenerateMobs(worldArea);
    }
}