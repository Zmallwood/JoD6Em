/*
 * GenerateNewWorld.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateNewWorld.hpp"
#include "World.hpp"
#include "Process/ClearWithGrass.hpp"
#include "Process/GenerateCreatures.hpp"
#include "Process/GenerateObjects.hpp"
#include "Process/GenerateWater.hpp"
#include "Process/GenerateRoads.hpp"
#include "Process/GenerateElevation.hpp"
#include "Process/GenerateRock.hpp"
#include "Process/GenerateCastleYard.hpp"
#include "Process/GenerateHorseCarts.hpp"

namespace JoD {
    
    void GenerateNewWorld() {
        
        auto worldArea = _<World>().GetCurrentWorldArea();
        
        // Do all generation steps.
        
        ClearWithGrass(worldArea);
        GenerateWater(worldArea);
        GenerateElevation(worldArea);
        GenerateRock(worldArea);
        GenerateCastleYard(worldArea);
        GenerateObjects(worldArea);
        GenerateRoads(worldArea);
        GenerateHorseCarts(worldArea);
        GenerateCreatures(worldArea);
    }
}