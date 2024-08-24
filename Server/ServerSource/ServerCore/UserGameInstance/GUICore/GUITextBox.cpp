/*
 * GUITextBox.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUITextBox.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/UserGameInstance/Cursor/Cursor.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"

namespace JoD {
GUITextBox::GUITextBox(BoxF bounds, GUIComponent *parent) :
    GUIComponent(bounds.GetPosition(), parent), m_size(bounds.GetSize()) {}

void GUITextBox::UpdateDerived(UserID userID) {
// Rertieve current mouse position.
    auto mousePos = _<EngineGet>().GetMousePosition(userID).value();
// Update hovered status.
    auto hovered = GetBounds().Contains(mousePos);
    if (hovered) {
        auto cursor = _<EngineGet>().GetCursor(userID);
// Change cursor type to hovered type if button is hovered.
        cursor->SetCursorType(CursorTypes::TextInput);
    }
    auto mouseInput =
        _<EngineGet>().GetMouseInput(userID);
// If button is hovered and mouse is clicked...
    if (hovered && mouseInput->GetLeftButton().GetIsPressed()) {}
}

void GUITextBox::RenderDerived(UserID userID) const {
    UserSendDrawImage(userID, "GUITextBoxBground", GetBounds());;
}

BoxF GUITextBox::GetBounds() const {
// Combine position and size to get bounds.
    return {m_position.x, m_position.y, m_size.w, m_size.h};
}
}
