/*
 * GenerateCreatures.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GenerateCreatures.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Creature.hpp"

namespace JoD {

namespace {

// Sent as argument to creature group generation function.
struct GenerateCreatureGroupOfTypeArgs {
    
    WorldArea* worldArea;             // World area to generate creatures in.
    std::string creatureName;         // Name of creature to generate.
    int numGroups;                    // Number of groups of the creature type to generate.
    int numCreaturesInGroup;          // Number of creatures in one generated group.
    Box area;                         // Area in the world area where the groups will be spawned.
    int creatureLevel;                // Level of creatures that are generated, determines how strong they area.
};

void GenerateCreatureGroupOfType(GenerateCreatureGroupOfTypeArgs args);

}

void GenerateCreatures(WorldArea* worldArea) {
    
    // Generate different kind of creatures at different parts of the world area,
    // cows are generated all over the world area.
    
    GenerateCreatureGroupOfType(
        {.worldArea = worldArea, .creatureName="CreatureBlueSlime",
         .numGroups = 6, .numCreaturesInGroup = 6,
         .area = {50, 0, 50, 50}, .creatureLevel=1});
    
    GenerateCreatureGroupOfType(
        {.worldArea = worldArea, .creatureName="CreatureYellowSlime",
         .numGroups = 6, .numCreaturesInGroup = 6,
         .area = {50, 50, 50, 50}, .creatureLevel=2});
    
    GenerateCreatureGroupOfType(
        {.worldArea = worldArea, .creatureName="CreatureRedSlime",
         .numGroups = 6, .numCreaturesInGroup = 6,
         .area = {0, 50, 50, 50}, .creatureLevel=3});
    
    GenerateCreatureGroupOfType(
        {.worldArea = worldArea, .creatureName="CreatureCow",
         .numGroups = 6, .numCreaturesInGroup = 6,
         .area = {0, 0, 100, 100}, .creatureLevel=3});
}

namespace {

void GenerateCreatureGroupOfType(GenerateCreatureGroupOfTypeArgs args) {
    
    // Loop for each group to generate.
    for (auto i = 0; i < args.numGroups; i++) {
        
        // Get center point of the group.
        const auto xCenter = rand() % args.area.w + args.area.x;
        const auto yCenter = rand() % args.area.h + args.area.y;
        
        // Create new group.
        CreatureGroup creatureGroup;
        
        // Set its center coordinate.
        creatureGroup.m_coord = {xCenter, yCenter};
        
        // Loop for each creature to spawn.
        for (auto j = 0; j < args.numCreaturesInGroup; j++) {
            
            // Place it randomly around the group center coordinate.
            const auto x = xCenter + rand() % 5 - rand() % 5;
            const auto y = yCenter + rand() % 5 - rand() % 5;
            
            // Dont spawn creatures outside the world area.
            if (!args.worldArea->IsValidCoord({x,y})) {
                
                continue;
            }
            
            // Dont spawn on top of another already existing creature.
            if (args.worldArea->GetTile(x, y)->GetCreature()) {
                
                continue;
            }
            
            // Dont spawn creatures in the water.
            if (args.worldArea->GetTile(
                    x,
                    y)->GetGround() ==
                Hash("GroundWater")) {
                
                continue;
            }
            
            // Creature a new creature object.
            const auto newCreature =
                std::make_shared<Creature>(
                    args.creatureName,
                    args.creatureLevel);
            
            // Add it to the group.
            creatureGroup.m_creatures.push_back(newCreature);
            
            // Register the creatures position to the world area.
            args.worldArea->RegisterCreaturePosition(
                newCreature,
                {x, y});
            
            // Add the new creature object to the tile its located at.
            args.worldArea->GetTile(x, y)->SetCreature(newCreature);
        }
        
        // Add the created creature group to the world area.
        args.worldArea->m_creatureGroups.push_back(creatureGroup);
    }
}

}
}