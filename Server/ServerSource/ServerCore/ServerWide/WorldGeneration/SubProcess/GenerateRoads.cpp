/*
 * GenerateRoads.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateRoads.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "ObjectsPile.hpp"

namespace JoD {
namespace {
// Argument packing for GenerateRoadSection() function.
struct GenerateRoadSectionArgs {
    WorldArea* worldArea;
    Point startCoord;
    Point deltaStep;
    int numSteps;
    std::vector<Point>& roadPath;
};

// Generate roads for a distance of tiles in the world area.
Point GenerateRoadSection(GenerateRoadSectionArgs args);
}

void GenerateRoads(WorldArea* worldArea) {
    std::vector<Point> roadPath;
// Start generating roads from top left corner of the world area.
    auto coord = Point {0, 0};
// Generate diagonal roads in south east direction.
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {1, 1},
         .numSteps = 25,
         .roadPath = roadPath});
// Generate straight road to the east.
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {1, 0},
         .numSteps = 50,
         .roadPath = roadPath});
// Generate straight road to the south.
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {0, 1},
         .numSteps = 50,
         .roadPath = roadPath});
// Generate straight road to the west.
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {-1, 0},
         .numSteps = 50,
         .roadPath = roadPath});
// Generate straight road to the south.
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {0, 1},
         .numSteps = 25,
         .roadPath = roadPath});
    worldArea->m_roadPath = roadPath;
}

namespace {
Point GenerateRoadSection(GenerateRoadSectionArgs args) {
    auto coord = args.startCoord;
// Iterate the provided distance of steps.
    for (auto i = 0; i < args.numSteps; i++) {
        args.roadPath.push_back(coord);
        auto tile = args.worldArea->GetTile(coord);
// If ground is grass
        if (tile->GetGround() == Hash("GroundGrass")) {
// Then create trail.
            tile->SetGround("GroundTrail");
        }
// If ground is cobblestone
        else if (tile->GetGround() == Hash("GroundCobbleStone")) {
// Then create slabs.
            tile->SetGround("GroundSlabs");
        }
// Else if ground is water
        else if (tile->GetGround() == Hash("GroundWater")) {
// Then create bridge.
            tile->SetGround("GroundBridge");
        }
        tile->GetObjectsPile().Clear();
// Move to next tile.
        coord += args.deltaStep;
    }
// Return the final tile which the generation ended on.
    return coord;
}
}
}