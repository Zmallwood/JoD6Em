/*
 * MouseMovement.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseMovement.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "TileHovering.hpp"
#include "CreatureTargeting.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
void MouseMovement::Update(UserID userID) {
// Get main scene.
    auto &mainScene = *_<EngineGet>().GetMainScene(userID);
// Get tile hovered component.
    auto tileHov =
        static_cast<TileHovering*>(mainScene.GetComponent(
                                       MainSceneComponents::TileHovering));
// Get creature targeting component.
    auto creaTarg =
        static_cast<CreatureTargeting*>(mainScene.GetComponent(
                                            MainSceneComponents::
                                            CreatureTargeting));
// Is left mouse button pressed.
    auto mouseDown =
        _<EngineGet>().GetMouseInput(
            userID)->GetLeftButton().GetIsPressedPickResult();
// Get player object.
    auto player = _<EngineGet>().GetPlayer(userID);
//Get hovered tile coordinate.
    auto hovTile = tileHov->GetHoveredCoord();
// If left mouse button is pressed and proper hovered tile coordinate has been obtained.
    if (mouseDown && hovTile.has_value()) {
// Set player destination to hovered tile coordinate.
        player->SetDestCoord(hovTile.value());
        player->SetTimeSetDest(Now());
// Clear any creature targeting.
        creaTarg->SetTargetedCreature(nullptr);
    }
// If its time for player to move.
    if (Now() >
        player->GetTimeLastMove() +
        Duration(Millis(static_cast<int>(1000/player->GetMoveSpd())))){
// If player has valid destination coordinate.
        if (player->GetDestCoord().has_value()){
// Get coordinate deltas.
            auto dx = player->GetDestCoord()->x - player->GetCoord().x;
            auto dy = player->GetDestCoord()->y - player->GetCoord().y;
// Move in direction according to deltas.
            if (dx < 0 && dy < 0)
                player->TryMove(userID, Directions::NorthWest);
            else if (dx == 0 && dy < 0)
                player->TryMove(userID, Directions::North);
            else if (dx > 0 && dy < 0)
                player->TryMove(userID, Directions::NorthEast);
            else if (dx > 0 && dy == 0)
                player->TryMove(userID, Directions::East);
            else if (dx > 0 && dy > 0)
                player->TryMove(userID, Directions::SouthEast);
            else if (dx == 0 && dy > 0)
                player->TryMove(userID, Directions::South);
            else if (dx < 0 && dy > 0)
                player->TryMove(userID, Directions::SouthWest);
            else if (dx < 0 && dy == 0)
                player->TryMove(userID, Directions::West);
// If any of the delta components got a value (i.e. destination is not equal to current position)
            if (dx || dy)
// Player has moved so update time property.
                player->SetTimeLastMove(Now());
            else
// Player has reached destination, clear destination property of player.
                player->SetDestCoord(std::nullopt);
        }
    }
}
}