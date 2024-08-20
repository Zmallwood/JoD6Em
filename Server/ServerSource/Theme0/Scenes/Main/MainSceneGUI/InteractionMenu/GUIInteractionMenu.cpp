/*
 * GUIInteractionMenu.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUIInteractionMenu.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Cursor/Cursor.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "Theme0/Scenes/Main/SubProcess/MainSceneComponents.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "ObjectsPile.hpp"
#include "Object.hpp"
#include "Theme0/Scenes/Main/SubProcess/TileHovering.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "Actions/ChopTreeAction.hpp"
#include "Actions/ChopFelledTreeAction.hpp"

namespace JoD {
GUIInteractionMenu::GUIInteractionMenu()
    : GUIComponent({0.0f, 0.0f}) {}

void GUIInteractionMenu::UpdateDerived(UserID userID) {
// Get necessary objects from engine and main scene.
    auto mouseInput = _<EngineGet>().GetMouseInput(userID);
    auto sceneManager = _<EngineGet>().GetSceneManager(userID);
    auto mainScene = sceneManager->GetScene<MainScene>("MainScene");
    auto tileHovering =
        static_cast<TileHovering*>(mainScene->GetComponent(
                                       MainSceneComponents::TileHovering));
    auto mousePosition = _<EngineGet>().GetMousePosition(userID).value();
// If right mouse button is pressed...
    if (mouseInput->GetRightButton().GetIsPressed()) {
// Get clicked tile.
        auto tile =
            _<World>().GetCurrWorldArea()->GetTile(
                tileHovering->GetHoveredCoord().value());
// Save clicked coordinate.
        m_clickedCoord = tileHovering->GetHoveredCoord().value();
// If tile contains a creature, cancel the menu activation.
        if (tile->GetCreature()) {
            m_active = false;
            return;
        }
// Make the menu appear at the clicked mouse position on the canvas.
        m_position = mousePosition;
// Activate the menu.
        m_active = true;
// Clear all previous menu entries to fill it with new ones.
        m_menuEntries.clear();
// To count the number of entries added to the meny.
        auto menuEntryIndex = 0;
// Loop over all objects on tile to determine what actions to add to the menu.
        for (auto object : tile->GetObjectsPile().GetObjects()) {
// If tile contains tree objects.
            if (object->GetType() == Hash("ObjectTree1") ||
                object->GetType() == Hash("ObjectTree2")){
// Add a chop down action to the menu.
                m_menuEntries.push_back(
                    {.label="Chop down tree", .action = Actions::chopTreeAction,
                     .bounds = {m_position.x,
                                m_position.y + menuEntryIndex*k_menuRowHeight,
                                m_size.w, k_menuRowHeight}});
// Increase added entries counter.
                menuEntryIndex++;
            }
            else if (object->GetType() == Hash("ObjectFelledTree")) {
// Add a chop up action to the menu.
                m_menuEntries.push_back(
                    {.label="Chop up felled tree", .action = Actions::chopFelledTreeAction,
                     .bounds = {m_position.x,
                                m_position.y + menuEntryIndex*k_menuRowHeight,
                                m_size.w, k_menuRowHeight}});
// Increase added entries counter.
                menuEntryIndex++; 
            }
        }
    }
    auto leftButtonPressed = mouseInput->GetLeftButton().GetIsPressed();
// Loop over all current menu entries in the menu.
    for (auto menuEntry: m_menuEntries) {
        auto bounds = menuEntry.bounds;
// If mosue is hovered over one of the entries...
        if (bounds.Contains(mousePosition)) {
            _<EngineGet>().GetCursor(userID)->SetCursorType(
                CursorTypes::Hovering);
            // If left mouse button is pressed...
            if (leftButtonPressed)
// Perform its action.
                menuEntry.action(m_clickedCoord);
        }
    }
    if (leftButtonPressed)
        m_active = false;
}

void GUIInteractionMenu::RenderDerived(UserID userID) const {
// Cancel rendering if menu isnt active.
    if (!m_active)
        return;
// Draw menu background image.
    UserSendDrawImage(userID, "GUIPanelBground", GetBounds());
// Start rendering menu rows at menus top left corner position.
    auto linePos = m_position;
// Loop over all current menu entries.
    for (auto menuEntry : m_menuEntries) {
// Draw the label of the menu entry on its own row.
        UserSendDrawText(userID, menuEntry.label, linePos);
// Translate y position downwards for every entry.
        linePos.y += k_menuRowHeight;
    }
}

BoxF GUIInteractionMenu::GetBounds() const {
// Combine position and size to obtain bounds.
    return {m_position.x, m_position.y, m_size.w, m_size.h};
}
}