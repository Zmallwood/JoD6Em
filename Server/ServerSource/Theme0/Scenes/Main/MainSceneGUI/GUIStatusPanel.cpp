/*
 * GUIStatusPanel.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUIStatusPanel.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "Theme0/Scenes/Main/MainSceneMath/ExperienceMath.hpp"

namespace JoD {

GUIStatusPanel::GUIStatusPanel()
    : GUIPanel({0.0f, 0.0f, k_width, k_height}) {}

void GUIStatusPanel::RenderDerived(UserID userID) const {
    
    GUIPanel::RenderDerived(userID);
    
    auto player = _<EngineGet>().GetPlayer(userID);
    
    SendTextDrawInstruction(userID, player->GetName(), {0.01f, 0.01f});
    
    auto level = GetCurrLevel(player->GetExperience());
    
    SendTextDrawInstruction(
        userID, "Level: " + std::to_string(level),
        {0.01f, 0.031f});
    
    auto hpText = "HP: " + std::to_string(player->GetHP()) + " / " +
                  std::to_string(player->GetMaxHP());
    
    SendTextDrawInstruction(userID, hpText, {0.01f, 0.052f});
    
    auto hpBarBox = BoxF {0.08f, 0.053f, 0.06f, 0.02f};
    
    SendImageDrawInstruction(userID, "Black", hpBarBox);
    
    auto hpFrac = static_cast<float>(player->GetHP())/player->GetMaxHP();
    
    auto hpBarBoxFilled = BoxF {hpBarBox.x, hpBarBox.y, hpBarBox.w*hpFrac,
                                hpBarBox.h};
    
    SendImageDrawInstruction(userID, "Red", hpBarBoxFilled);
}

}