/*
 * WorldView.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "WorldView.hpp"
#include "Configuration/GameProperties.hpp"
#include "Theme0/Scenes/Main/MainSceneMath/TileGridMath.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/Tile.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "Process/RenderGround.hpp"
#include "Process/RenderTileSymbols.hpp"
#include "Process/RenderObjects.hpp"
#include "Process/RenderMobs.hpp"
#include "Process/RenderPlayer.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    
    void WorldView::Render(UserID userID) const {
        
        auto &webSocket = *_<EngineGet>().GetWebSocket(userID);
        
        const auto tileSize =
            CalculateTileSize(
                _<EngineGet>().GetAspectRatio(userID).value());
        
        const auto playerCoordinate =
            _<EngineGet>().GetPlayer(userID)->GetCoord();
        
        auto playerElev =
            _<World>().GetCurrentWorldArea()->GetTile(
                playerCoordinate)->GetElevation();
        
        const auto numGridRows = _<GameProperties>().GetNumGridRows();
        const auto numGridCols =
            CalculateNumGridCols(
                _<EngineGet>().GetAspectRatio(userID).value());
        
        auto &mainScene = *_<EngineGet>().GetSceneManager(userID)->GetScene<MainScene>("MainScene");
        
        const auto smallValue = 0.0001f;
        
        for (auto y = 0; y < numGridRows; y++){
            
            for (auto x = 0; x < numGridCols; x++){
                
                const auto coordX = playerCoordinate.x -
                                    (numGridCols - 1) / 2 + x;
                
                const auto coordY = playerCoordinate.y -
                                    (numGridRows - 1) / 2 + y;
                
                if (!_<World>().GetCurrentWorldArea()->IsValidCoord({coordX,
                                                                     coordY})) {
                    
                    continue;
                }
                
                auto tile =
                    _<World>().GetCurrentWorldArea()->GetTile(
                        coordX,
                        coordY);
                
                auto elev = tile->GetElevation();
                
                const auto groundBounds = BoxF {
                    x * tileSize.w + playerElev*tileSize.w*0.25f,
                    y * tileSize.h + playerElev*tileSize.h*0.25f,
                    tileSize.w + smallValue,
                    tileSize.h + smallValue};
                
                Tile* tileW = nullptr;
                Tile* tileN = nullptr;
                
                if (coordX > 0) {
                    
                    tileW = _<World>().GetCurrentWorldArea()->GetTile(coordX -
                                                                      1,
                                                                      coordY);
                    tileN = _<World>().GetCurrentWorldArea()->GetTile(coordX,
                                                                      coordY -
                                                                      1);
                }
                
                RenderGround(webSocket, tile, groundBounds, tileW, tileN,
                             playerElev);
                
                
                
                const auto tileBounds = BoxF {
                    x * tileSize.w + (playerElev - elev)*tileSize.w*0.25f,
                    y * tileSize.h + (playerElev - elev)*tileSize.h*0.25f,
                    tileSize.w + smallValue,
                    tileSize.h + smallValue};
                
                RenderTileSymbols(
                    mainScene, userID, webSocket,
                    {coordX, coordY}, tileBounds);
                
                RenderObjects(webSocket, tile, tileBounds);
                
                RenderMobs(
                    mainScene, webSocket, tile,
                    tileBounds);
                
                auto playerBounds =  BoxF {
                    x * tileSize.w,
                    y * tileSize.h,
                    tileSize.w + smallValue,
                    tileSize.h + smallValue};
                
                RenderPlayer(
                    userID, webSocket, {coordX, coordY},
                    playerBounds);
            }
        }
    }
}