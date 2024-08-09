/*
 * GUITextConsole.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUITextConsole.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/UserGameInstance/TextOutput/TextMessages.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
    GUITextConsole::GUITextConsole()
        : GUIPanel({0.0f, 1.0f - k_height, k_width, k_height}) {
        
    }
    
    
    void GUITextConsole::RenderDerived(UserID userID,
                                       WebSocket& webSocket) const {
        
        GUIPanel::RenderDerived(userID, webSocket);
        
        auto engineInstance = _<EngineGet>().GetInstance(userID);
        
        auto textOut = engineInstance->TextOut();
        
        auto& textData = textOut->Data();
        
        auto lineY = m_position.y + k_margin;
        
        
        for (auto i = 0; i < textData.size(); i++) {
            
            SendTextDrawInstruction(webSocket, textData.at(i), {m_position.x + k_margin, lineY});
            
            lineY += k_lineHeight;
        }
    }
}