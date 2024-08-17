/*
 * GenerateNewWorld.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateNewWorld.hpp"
#include "World.hpp"
#include "SubProcess/ClearWithGrass.hpp"
#include "SubProcess/GenerateCreatures.hpp"
#include "SubProcess/GenerateObjects.hpp"
#include "SubProcess/GenerateWater.hpp"
#include "SubProcess/GenerateRoads.hpp"
#include "SubProcess/GenerateElevation.hpp"
#include "SubProcess/GenerateRock.hpp"
#include "SubProcess/GenerateCastleYard.hpp"
#include "SubProcess/GenerateHorseCarts.hpp"
#include "SubProcess/GenerateNPCs.hpp"

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
        GenerateNPCs(worldArea);
        GenerateCreatures(worldArea);
    }
}