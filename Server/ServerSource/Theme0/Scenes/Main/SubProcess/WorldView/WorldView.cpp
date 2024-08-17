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

        auto &webSocket = *_<EngineGet>().GetWebSocket(userID);

        const auto tileSize =
            CalculateTileSize(
                _<EngineGet>().GetAspectRatio(userID).value());

        const auto playerCoordinate =
            _<EngineGet>().GetPlayer(userID)->GetCoord();

        auto playerElev =
            _<World>().GetCurrWorldArea()->GetTile(
                playerCoordinate)->GetElevation();

        const auto numGridRows = _<GameProperties>().GetNumGridRows();
        const auto numGridCols =
            CalculateNumGridCols(
                _<EngineGet>().GetAspectRatio(userID).value());

        auto &mainScene = *_<EngineGet>().GetSceneManager(userID)->GetScene<MainScene>("MainScene");

        const auto smallValue = 0.0001f;

        auto tilesMargin = 3;

        for (auto y = -tilesMargin; y < numGridRows + tilesMargin; y++){

            for (auto x = -tilesMargin; x < numGridCols + tilesMargin; x++){

                const auto coordX = playerCoordinate.x -
                                    (numGridCols - 1) / 2 + x;

                const auto coordY = playerCoordinate.y -
                                    (numGridRows - 1) / 2 + y;

                if (!_<World>().GetCurrWorldArea()->IsValidCoord({coordX,
                                                                     coordY})) {

                    continue;
                }

                auto tile =
                    _<World>().GetCurrWorldArea()->GetTile(
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

                    tileW = _<World>().GetCurrWorldArea()->GetTile(coordX -
                                                                      1,
                                                                      coordY);
                    tileN = _<World>().GetCurrWorldArea()->GetTile(coordX,
                                                                      coordY -
                                                                      1);
                }

                RenderGround(userID, tile, groundBounds, tileW, tileN,
                             playerElev);



                const auto tileBounds = BoxF {
                    x * tileSize.w + (playerElev - elev)*tileSize.w*0.25f,
                    y * tileSize.h + (playerElev - elev)*tileSize.h*0.25f,
                    tileSize.w + smallValue,
                    tileSize.h + smallValue};

                RenderTileSymbols(
                    mainScene, userID,
                    {coordX, coordY}, tileBounds);

                RenderObjects(userID, tile, tileBounds);

                RenderNPCs(
                    userID, tile,
                    tileBounds);

                RenderCreatures(
                    mainScene, userID, tile,
                    tileBounds);

                auto playerBounds =  BoxF {
                    x * tileSize.w,
                    y * tileSize.h,
                    tileSize.w + smallValue,
                    tileSize.h + smallValue};

                RenderPlayer(
                    userID, {coordX, coordY},
                    playerBounds);
            }
        }
    }
}
