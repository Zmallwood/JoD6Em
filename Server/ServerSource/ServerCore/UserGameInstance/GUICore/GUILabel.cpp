/*
 * GUILabel.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUILabel.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    GUILabel::GUILabel(PointF position, std::string_view text)
        : m_text(text), GUIComponent(position) {
        
    }
    
    void GUILabel::RenderDerived(WebSocket& webSocket){
        
        SendTextDrawInstruction(webSocket, m_text, m_position);
    }
}