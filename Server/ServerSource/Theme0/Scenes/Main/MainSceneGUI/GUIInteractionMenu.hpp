/*
 * GUIInteractionMenu.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/GUICore/GUIComponent.hpp"

namespace JoD {
    
    class GUIInteractionMenu : public GUIComponent {
        
      public:
        GUIInteractionMenu();
        
        void UpdateDerived(UserID userID) override;
        
        void RenderDerived(UserID userID) const override;
        
      private:
        BoxF GetBounds() const;
        
        SizeF m_size {0.1f, 0.05f};
        bool m_active {false};
    };
}