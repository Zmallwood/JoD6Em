/*
 * GUIButton.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUIButton.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Cursor/Cursor.hpp"

namespace JoD {
GUIButton::GUIButton(BoxF bounds, std::string_view text,
                     std::function<void()> action,
                     std::string_view imageNameDefault,
                     std::string_view imageNameHovered,
                     GUIComponent *parent)
    :  m_text(text), GUIComponent(bounds.GetPosition(), parent),
    m_size(bounds.GetSize()), m_action(action),
    m_imageNameDefault(imageNameDefault),
    m_imageNameHovered(imageNameHovered) {}

GUIButton::GUIButton(BoxF bounds, std::string_view text,
                     std::function<void()> action, GUIComponent *parent) :
    m_text(text), GUIComponent(bounds.GetPosition(), parent),
    m_size(bounds.GetSize()), m_action(action) {}

void GUIButton::UpdateDerived(UserID userID) {
// Rertieve current mouse position.
    auto mousePos = _<EngineGet>().GetMousePosition(userID).value();
// Update hovered status.
    m_hovered = GetBounds().Contains(mousePos);
    if (m_hovered) {
        auto cursor = _<EngineGet>().GetCursor(userID);
// Change cursor type to hovered type if button is hovered.
        cursor->SetCursorType(CursorTypes::Hovering);
    }
    auto mouseInput =
        _<EngineGet>().GetMouseInput(userID);
// If button is hovered and mouse is clicked...
    if (m_hovered && mouseInput->GetLeftButton().GetIsPressed()) {
// Perform button action.
        m_action();
    }
}

void GUIButton::RenderDerived(UserID userID) const {
// Get right button image.
    std::string imageName =
        m_hovered ? m_imageNameHovered : m_imageNameDefault;
// Draw button image.
    UserSendDrawImage(userID, imageName, GetBounds());;
// Draw text on button.
    UserSendDrawText(
        userID, m_text, GetBounds().GetCenter(),
        true);
}

BoxF GUIButton::GetBounds() const {
// Combine position and size to get bounds.
    return {m_position.x, m_position.y, m_size.w, m_size.h};
}
}
