/*
 * GUILabel.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUILabel.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
GUILabel::GUILabel(PointF position, std::string_view text,
                   bool centerAligned, GUIComponent *parent)
    : m_text(text), GUIComponent(position, parent),
    m_centerAligned(centerAligned) {}

void GUILabel::RenderDerived(UserID userID) const {
// Draw the labels text to canvas.
    UserSendDrawText(userID, m_text, m_position, m_centerAligned);
}
}
