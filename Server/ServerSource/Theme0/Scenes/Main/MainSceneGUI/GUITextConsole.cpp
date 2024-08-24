/*
 * GUITextConsole.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUITextConsole.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/UserGameInstance/TextOutput/TextMessages.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "GUIExpBar.hpp"

namespace JoD {

GUITextConsole::GUITextConsole(GUIComponent *parent)
    : GUIPanel({0.0f, 1.0f - k_height - GUIExpBar::GetHeight(), k_width,
                k_height}, parent) {}


void GUITextConsole::RenderDerived(UserID userID) const {
// Call base class function which renders the bacground image.
    GUIPanel::RenderDerived(userID);
// Get text messages data.
    auto textMessages = _<EngineGet>().GetTextMessages(userID);
    auto& textData = textMessages->GetData();
// To hold the y position of current line.
    auto lineY = m_position.y + k_margin;
// Maximum number of lines that fit in the text console.
    auto numLines = static_cast<int>((k_height - 2*k_margin)/k_lineHeight);
// If number of text lines is less than the max...
    if (textData.size() <= numLines) {
// Loop of the all the text lines.
        for (auto i = 0; i < textData.size(); i++) {
// Draw the text line.
            UserSendDrawText(
                userID, textData.at(i),
                {m_position.x + k_margin, lineY});
// Alter the y position for the next text line.
            lineY += k_lineHeight;
        }
    }
// Else if number of text lines exceeds the maximum.
    else {
// Only loop over the last text lines in the data.
        for (auto i = textData.size() - numLines; i < textData.size(); i++) {
// Draw the the line.
            UserSendDrawText(
                userID, textData.at(i),
                {m_position.x + k_margin, lineY});
// Alter the y position for the next text line.
            lineY += k_lineHeight;
        }
    }
}
}
