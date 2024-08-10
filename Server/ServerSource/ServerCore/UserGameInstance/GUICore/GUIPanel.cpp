/*
 * GUIPanel.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUIPanel.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    
    GUIPanel::GUIPanel(BoxF bounds)
        : GUIComponent(bounds.GetPosition()), m_size(bounds.GetSize()) {
        
    }
    
    void GUIPanel::RenderDerived(UserID userID) const {
        
        auto &webSocket = *_<EngineGet>().GetWebSocket(userID);
        
        SendImageDrawInstruction(webSocket, "GUIPanelBground", GetBounds());
    }
    
    BoxF GUIPanel::GetBounds() const {
        
        return {m_position.x, m_position.y, m_size.w, m_size.h};
    }
}