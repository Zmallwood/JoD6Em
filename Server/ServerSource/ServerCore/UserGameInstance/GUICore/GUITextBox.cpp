/*
 * GUITextBox.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUITextBox.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
GUITextBox::GUITextBox(BoxF bounds) :
    GUIComponent(bounds.GetPosition()), m_size(bounds.GetSize()) {}

void GUITextBox::RenderDerived(UserID userID) const {
    UserSendDrawImage(userID, "GUITextBoxBground", GetBounds());;
}

BoxF GUITextBox::GetBounds() const {
// Combine position and size to get bounds.
    return {m_position.x, m_position.y, m_size.w, m_size.h};
}
}
