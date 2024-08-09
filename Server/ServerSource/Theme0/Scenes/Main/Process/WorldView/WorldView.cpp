/*
 * WorldView.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "WorldView.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "Configuration/GameProperties.hpp"
#include "Theme0/Scenes/Main/MainSceneMath/TileGridMath.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/ServerWide/WorldStructure/World.hpp"
#include "ServerCore/ServerWide/WorldStructure/WorldArea.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "Process/RenderGround.hpp"
#include "Process/RenderTileSymbols.hpp"
#include "Process/RenderObjects.hpp"
#include "Process/RenderMobs.hpp"
#include "Process/RenderPlayer.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"

namespace JoD {
    
    void WorldView::Render(UserID userID, WebSocket &webSocket) const {
        
        const auto tileSize =
            CalculateTileSize(
                EngineInstance().GetAspectRatio());
        
        const auto playerCoordinate =
            EngineInstance().Player()->Coord();
        
        const auto numGridRows = _<GameProperties>().GetNumGridRows();
        const auto numGridCols =
            CalculateNumGridCols(
                EngineInstance().GetAspectRatio());
                
        auto &mainScene = *EngineInstance().SceneManager()->GetScene<MainScene>("MainScene");
        
        const auto smallValue = 0.0001f;
        
        for (auto y = 0; y < numGridRows; y++){
            
            for (auto x = 0; x < numGridCols; x++){
                
                const auto coordX = playerCoordinate.x -
                                    (numGridCols - 1) / 2 + x;
                
                const auto coordY = playerCoordinate.y -
                                    (numGridRows - 1) / 2 + y;
                
                if (!_<World>().GetCurrentWorldArea()->IsValidCoord({coordX, coordY})) {
                    
                    continue;
                }
                
                auto tile =
                    _<World>().GetCurrentWorldArea()->GetTile(coordX,
                        coordY);
                
                const auto tileBounds = BoxF {
                    x * tileSize.w, y * tileSize.h,
                    tileSize.w + smallValue,
                    tileSize.h + smallValue};
                
                RenderGround(webSocket, tile, tileBounds);
                
                RenderTileSymbols(
                    mainScene, EngineInstance(), webSocket,
                    {coordX, coordY}, tileBounds);
                
                RenderObjects(webSocket, tile, tileBounds);
                
                RenderMobs(
                    mainScene, webSocket, tile,
                    tileBounds);
                
                RenderPlayer(
                    EngineInstance(), webSocket, {coordX, coordY},
                    tileBounds);
            }
        }
    }
}