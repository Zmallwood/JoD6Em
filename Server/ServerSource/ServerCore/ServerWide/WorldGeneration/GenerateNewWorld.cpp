/*
 * GenerateNewWorld.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateNewWorld.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "Process/ClearWithGrass.hpp"
#include "Process/GenerateCreatures.hpp"
#include "Process/GenerateObjects.hpp"
#include "Process/GenerateWater.hpp"
#include "Process/GenerateRoads.hpp"
#include "Process/GenerateElevation.hpp"
#include "Process/GenerateRock.hpp"

namespace JoD {
    
    void GenerateNewWorld() {
        
        auto worldArea = _<World>().GetCurrentWorldArea();
        
        ClearWithGrass(worldArea);
        GenerateWater(worldArea);
        GenerateElevation(worldArea);
        GenerateRock(worldArea);
        GenerateRoads(worldArea);
        GenerateObjects(worldArea);
        GenerateCreatures(worldArea);
    }
}