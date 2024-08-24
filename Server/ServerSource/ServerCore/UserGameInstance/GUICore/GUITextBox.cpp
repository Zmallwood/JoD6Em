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
#include "GUI.hpp"
#include "ServerCore/UserGameInstance/Input/Keyboard/KeyboardInput.hpp"

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
    if (hovered && mouseInput->GetLeftButton().GetIsPressed()) {
        auto gui = GetRootGUI();
        gui->SetFocusedTextBox(this);
    }
    
    if (GetRootGUI()->GetFocusedTextBox() == this)
        m_managedText.AppendText(
            _<EngineGet>().GetKeyboardInput(userID)->GetTextInputPickResult());
}

void GUITextBox::RenderDerived(UserID userID) const {
    UserSendDrawImage(userID, "GUITextBoxBground", GetBounds());;
    if (GetRootGUI()->GetFocusedTextBox() == this) {
        auto blinkCursor = (Now().time_since_epoch().count() % 2000000)/
                           1000000;
        if (blinkCursor) {
            auto cursorBounds = BoxF {m_position.x, m_position.y,
                                      k_cursorWidth, m_size.h};
            UserSendDrawImage(userID, "GUITextBoxTextCursor", cursorBounds);
        }
    }
    UserSendDrawText(userID, m_managedText.GetText(), m_position);
}

BoxF GUITextBox::GetBounds() const {
// Combine position and size to get bounds.
    return {m_position.x, m_position.y, m_size.w, m_size.h};
}

std::string GUITextBox::GetText() const {
    return m_managedText.GetText();
}
}
