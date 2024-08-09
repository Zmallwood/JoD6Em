/*
 * GUIPanel.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUIPanel.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    
    GUIPanel::GUIPanel(BoxF bounds)
        : GUIComponent(bounds.GetPosition()), m_size(bounds.GetSize()) {
        
    }
    
    void GUIPanel::RenderDerived(UserID userID, WebSocket& webSocket) const {
        
        SendImageDrawInstruction(webSocket, "GUIPanelBground", GetBounds());
    }
    
    BoxF GUIPanel::GetBounds() const {
        
        return {m_position.x, m_position.y, m_size.w, m_size.h};
    }
}