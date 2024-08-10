/*
 * GUIExpBar.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/GUICore/GUIComponent.hpp"

namespace JoD {
    
    class GUIExpBar : public GUIComponent {
        
      public:
        GUIExpBar();
        
        void UpdateDerived(UserID userID) override;
        
        void RenderDerived(UserID userID) const override;
        
        static constexpr float GetHeight() {
            
            return k_height;
        }
        
      private:
        float m_filledAmount {0.0f};
        static constexpr float k_height {0.03f};
    };
}