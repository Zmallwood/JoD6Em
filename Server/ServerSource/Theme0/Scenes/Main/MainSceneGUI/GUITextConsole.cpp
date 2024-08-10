/*
 * GUITextConsole.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUITextConsole.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/UserGameInstance/TextOutput/TextMessages.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "GUIExpBar.hpp"

namespace JoD {
    GUITextConsole::GUITextConsole()
        : GUIPanel({0.0f, 1.0f - k_height - GUIExpBar::GetHeight(), k_width, k_height}) {
        
    }
    
    
    void GUITextConsole::RenderDerived(UserID userID) const {
        
        GUIPanel::RenderDerived(userID);
        
        auto &webSocket = *_<EngineGet>().GetWebSocket(userID);
        
        auto textOut = _<EngineGet>().GetTextMessages(userID);
        
        auto& textData = textOut->GetData();
        
        auto lineY = m_position.y + k_margin;
        
        
        for (auto i = 0; i < textData.size(); i++) {
            
            SendTextDrawInstruction(webSocket, textData.at(i), {m_position.x + k_margin, lineY});
            
            lineY += k_lineHeight;
        }
    }
}