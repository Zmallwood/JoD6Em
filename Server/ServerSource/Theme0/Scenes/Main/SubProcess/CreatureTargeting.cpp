/*
 * CreatureTargeting.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "CreatureTargeting.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "TileHovering.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
void CreatureTargeting::Update(UserID userID) {
// Get player object.
    auto player =
        _<EngineGet>().GetPlayer(userID);
// Get main scene object.
    auto mainScene =
        _<EngineGet>().GetSceneManager(userID)->GetScene<MainScene>(
            "MainScene");
// Get tile hovering component.
    auto tileHov =
        static_cast<TileHovering*>(
            mainScene->GetComponent(
                MainSceneComponents::
                TileHovering));
// Is mouse pressed down.
    const auto mouseDown =
        _<EngineGet>().GetMouseInput(userID)->
        GetRightButton().
        GetIsPressedPickResult();
// Get hovered tile.
    const auto hovTile = tileHov->GetHoveredCoord();
// If left mouse button is pressed and a proper tile coordinate is hovered.
    if (mouseDown && hovTile.has_value()) {
//Clear players destination coordinate.
        player->SetDestCoord(std::nullopt);
// Get hovered tile.
        const auto &wArea = _<World>().GetCurrWorldArea();
        const auto &tile = wArea->GetTile(hovTile.value());
// If hovered tile has a creature, target it,
// otherwise clear current creature target.
        if (tile->GetCreature())
            m_targetedCreature = tile->GetCreature();
        else
            m_targetedCreature = nullptr;
    }
}
}