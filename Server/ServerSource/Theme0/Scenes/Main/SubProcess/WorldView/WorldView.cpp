/*
 * WorldView.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "WorldView.hpp"
#include "Configuration/GameProperties.hpp"
#include "Theme0/Scenes/Main/MainSceneMath/TileGridMath.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "World.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "SubProcess/RenderGround.hpp"
#include "SubProcess/RenderTileSymbols.hpp"
#include "SubProcess/RenderObjects.hpp"
#include "SubProcess/RenderCreatures.hpp"
#include "SubProcess/RenderPlayer.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "SubProcess/RenderNPCs.hpp"

namespace JoD {

void WorldView::Render(UserID userID) const {
    
// Get tile size.
    auto tileSz = CalcTileSize(
        _<EngineGet>().GetAspectRatio(userID).value());
    
// Get player coordinate.
    auto playerCoord = _<EngineGet>().GetPlayer(userID)->GetCoord();
    
// Get current world area.
    auto currWArea = _<World>().GetCurrWorldArea();
    
// Get tile elevation at player coordinate.
    auto playerElev = currWArea->GetTile(playerCoord)->GetElevation();
    
// Determine dimensions of tile grid.
    auto numGridRows = _<GameProperties>().GetNumGridRows();
    auto numGridCols =
        CalcNumGridCols(_<EngineGet>().GetAspectRatio(userID).value());
    
// Used to make tiles slightly overlap each other to avoid some graphical artifacts.
    auto smallValue = 0.0001f;
    
// Value by which tiles are rendered outside the visible canvas, as otherwise sometimes
// elevation differences results in unrendered areas in the canvas.
    auto tilesMargin = 2;
    
// Loop over the tile grid from top to bottom.
    for (auto y = -tilesMargin; y < numGridRows + tilesMargin; y++){
        
// Loop over one row in the tile grid from left to right.
        for (auto x = -tilesMargin; x < numGridCols + tilesMargin; x++){
            
// Determine the coordinate for this iterations tile.
            auto coordX = playerCoord.x - (numGridCols - 1) / 2 + x;
            auto coordY = playerCoord.y - (numGridRows - 1) / 2 + y;
            
// Skip processing if not a valid tile coordinate.
            if (!currWArea->IsValidCoord({coordX, coordY})) {
                
                continue;
            }
            
// Obtain the tile object.
            auto tile = currWArea->GetTile(coordX, coordY);
            
// Create bounds for ground offseted with regards to player elevation
// but without elevating the tile.
            auto groundBounds = BoxF {
                x * tileSz.w + playerElev*tileSz.w*0.25f,
                y * tileSz.h + playerElev*tileSz.h*0.25f,
                tileSz.w + smallValue,
                tileSz.h + smallValue};
            
// To hold west and north tile neighbours.

            Tile* tileW = nullptr;
            Tile* tileN = nullptr;
            
// Can only create west neighbour if not at the west edge.
            if (coordX > 0) {
                
                tileW = currWArea->GetTile(
                    coordX - 1, coordY);
            }

// Can only create north neighbour if not at the north edge.
            if (coordY > 0) {
                
                tileN = currWArea->GetTile(
                    coordX, coordY - 1);
            }
            
// Draw the ground surface.
            RenderGround(
                userID, tile, groundBounds, tileW, tileN,
                playerElev);
            
            auto elev = tile->GetElevation();
            
// Create bounds for tile, elevated to tile height.
            auto tileBounds = BoxF {
                x * tileSz.w + (playerElev - elev)*tileSz.w*0.25f,
                y * tileSz.h + (playerElev - elev)*tileSz.h*0.25f,
                tileSz.w + smallValue,
                tileSz.h + smallValue};
            
// Render tile symbols on the ground.
            RenderTileSymbols(userID, {coordX, coordY}, tileBounds);
            
// Render objects on the tile.
            RenderObjects(userID, tile, tileBounds);
            
// Render NPC on the tile if there is one.
            RenderNPCs( userID, tile, tileBounds);
            
// Render creature on the tile if there is one.
            RenderCreatures(userID, tile, tileBounds);
            
// Render player if current tile is the one the player is located on.
            RenderPlayer(userID, {coordX, coordY}, tileBounds);
        }
    }
}

}
