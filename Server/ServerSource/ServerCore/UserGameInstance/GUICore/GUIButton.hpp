/*
 * GUIButton.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "GUIComponent.hpp"

namespace JoD {
    
    class GUIButton : public GUIComponent {
      public:
        GUIButton(BoxF bounds, std::string_view text, std::function<void()> action);
        
        void UpdateDerived(UserID userID) override;
        
        void RenderDerived(UserID userID) const override;
        
      private:
        BoxF GetBounds() const;
      
        std::string m_text;
        SizeF m_size;
        std::function<void()> m_action;
        bool m_hovered {false};
    };
}