/*
 * GUIExpBar.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUIExpBar.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "Theme0/Scenes/Main/MainSceneMath/ExperienceMath.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"

namespace JoD {
    
    GUIExpBar::GUIExpBar()
        : GUIComponent({0.0f, 1.0f - k_height}) {
        
    }
    
    void GUIExpBar::UpdateDerived(UserID userID) {
        
        auto player = _<EngineGet>().GetPlayer(userID);
        
        auto exp = player->GetExperience();
        
        m_filledAmount = GetFractionalExpProgress(exp);
    }
    
    void GUIExpBar::RenderDerived(UserID userID) const {
        
        auto &webSocket = *_<EngineGet>().GetWebSocket(userID);
        
        auto boundsBground = BoxF {m_position.x, m_position.y, 1.0f, k_height};
        
        SendImageDrawInstruction(webSocket, "Black", boundsBground);
        
        auto boundsFilled = BoxF {m_position.x, m_position.y, m_filledAmount, k_height};
        
        SendImageDrawInstruction(webSocket, "Gold", boundsFilled);
        
        auto boundsBorder = BoxF {m_position.x, m_position.y, 1.0f, 0.001f};
        
        SendImageDrawInstruction(webSocket, "White", boundsBorder);
    }
}