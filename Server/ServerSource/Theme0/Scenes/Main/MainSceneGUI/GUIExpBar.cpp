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
    : GUIComponent({0.0f, 1.0f - k_height}) {}

void GUIExpBar::UpdateDerived(UserID userID) {
    
// Get the player, its experience, and experience progress.
    
    auto player = _<EngineGet>().GetPlayer(userID);
    
    auto exp = player->GetExperience();
    
    m_filledAmount = CalcFractionalExpProgress(exp);
}

void GUIExpBar::RenderDerived(UserID userID) const {
    
// Create the exp bar background bounds and render the background.
    
    auto boundsBground = BoxF {m_position.x, m_position.y, 1.0f, k_height};
    
    UserSendDrawImage(userID, "Black", boundsBground);
    
// Create the exp bar filled background bounds and render the filled area.
    
    auto boundsFilled = BoxF {m_position.x, m_position.y, m_filledAmount,
                              k_height};
    
    UserSendDrawImage(userID, "Gold", boundsFilled);
    
// Create the exp bar border bounds and render the borders.
    
    auto boundsBorder = BoxF {m_position.x, m_position.y, 1.0f, 0.001f};
    
    UserSendDrawImage(userID, "White", boundsBorder);
}

}