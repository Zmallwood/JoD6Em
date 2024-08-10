/*
 * GUILabel.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUILabel.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    GUILabel::GUILabel(PointF position, std::string_view text, bool centerAligned)
        : m_text(text), GUIComponent(position), m_centerAligned(centerAligned) {
        
    }
    
    void GUILabel::RenderDerived(UserID userID) const {
        
        auto &webSocket = *_<EngineGet>().GetWebSocket(userID);
        
        SendTextDrawInstruction(webSocket, m_text, m_position, m_centerAligned);
    }
}