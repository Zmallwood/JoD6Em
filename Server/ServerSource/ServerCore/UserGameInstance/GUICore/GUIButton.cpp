/*
 * GUIButton.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUIButton.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Cursor/Cursor.hpp"

namespace JoD {
    GUIButton::GUIButton(BoxF bounds, std::string_view text,
                         std::function<void()> action)
        :  m_text(text), GUIComponent(bounds.GetPosition()),
        m_size(bounds.GetSize()), m_action(action){
        
    }
    
    void GUIButton::UpdateDerived(UserID userID) {
        
        auto mousePosition = _<EngineGet>().GetMousePosition(userID).value();
        
        m_hovered = GetBounds().Contains(mousePosition);
        
        if (m_hovered) {
            
            auto cursor = _<EngineGet>().GetCursor(userID);
            
            cursor->SetCursorType(CursorTypes::Hovering);
        }
        
        auto mouseInput =
            _<EngineGet>().GetMouseInput(userID);
            
        if (m_hovered && mouseInput->GetLeftButton().GetIsPressed()) {
            
            m_action();
        }
    }
    
    void GUIButton::RenderDerived(UserID userID) const {
        
        
        std::string imageName =
            m_hovered ? "GUIButtonHoveredBground" : "GUIButtonBground";
        
        SendImageDrawInstruction(userID, imageName, GetBounds());;
        
        SendTextDrawInstruction(
            userID, m_text, GetBounds().GetCenter(),
            true);
    }
    
    BoxF GUIButton::GetBounds() const {
        
        return {m_position.x, m_position.y, m_size.w, m_size.h};
    }
}