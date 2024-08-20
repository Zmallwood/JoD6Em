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
    auto coord = Point {1, 0};
// Generate diagonal roads in south east direction.
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {0, 1},
         .numSteps = 6,
         .roadPath = roadPath});
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {1, 0},
         .numSteps = 5,
         .roadPath = roadPath});
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {0, 1},
         .numSteps = 5,
         .roadPath = roadPath});
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {1, 0},
         .numSteps = 5,
         .roadPath = roadPath});
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {0, 1},
         .numSteps = 5,
         .roadPath = roadPath});
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {1, 0},
         .numSteps = 5,
         .roadPath = roadPath});
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {0, 1},
         .numSteps = 5,
         .roadPath = roadPath});
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {1, 0},
         .numSteps = 5,
         .roadPath = roadPath});
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {0, 1},
         .numSteps = 5,
         .roadPath = roadPath});
    coord = GenerateRoadSection(
        {.worldArea = worldArea,
         .startCoord = coord, .deltaStep = {1, 0},
         .numSteps = 5,
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
         .numSteps = 24,
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
        Tile* tileN = nullptr;
        Tile* tileE = nullptr;
        Tile* tileNE = nullptr;
        if (coord.y > 0)
            tileN = args.worldArea->GetTile(coord.x, coord.y-1);
        if (coord.x < args.worldArea->GetSize().w - 1)
            tileE = args.worldArea->GetTile(coord.x + 1, coord.y);
        if (coord.y > 0 && coord.x < args.worldArea->GetSize().w - 1)
            tileNE = args.worldArea->GetTile(coord.x + 1, coord.y - 1);
        if (tileN) {
            if (tileN->GetGround() == Hash("GroundGrass")) {
                tileN->SetGround("GroundTrail");
            }
            else if (tileN->GetGround() == Hash("GroundCobbleStone")) {
                tileN->SetGround("GroundSlabs");
            }
            else if (tileN->GetGround() == Hash("GroundWater")) {
                tileN->SetGround("GroundBridge");
            }
            tileN->GetObjectsPile().Clear();
        }
        if (tileE) {
            if (tileE->GetGround() == Hash("GroundGrass")) {
                tileE->SetGround("GroundTrail");
            }
            else if (tileE->GetGround() == Hash("GroundCobbleStone")) {
                tileE->SetGround("GroundSlabs");
            }
            else if (tileE->GetGround() == Hash("GroundWater")) {
                tileE->SetGround("GroundBridge");
            }
            tileE->GetObjectsPile().Clear();
        }
        if (tileNE) {
            if (tileNE->GetGround() == Hash("GroundGrass")) {
                tileNE->SetGround("GroundTrail");
            }
            else if (tileNE->GetGround() == Hash("GroundCobbleStone")) {
                tileNE->SetGround("GroundSlabs");
            }
            else if (tileNE->GetGround() == Hash("GroundWater")) {
                tileNE->SetGround("GroundBridge");
            }
            tileNE->GetObjectsPile().Clear();
        }
// Move to next tile.
        coord += args.deltaStep;
    }
// Return the final tile which the generation ended on.
    return coord;
}
}
}