/*
 * GUIStatusPanel.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/GUICore/GUIPanel.hpp"

namespace JoD {
    
    class GUIStatusPanel : public GUIPanel {
        
      public:
        GUIStatusPanel();
        
        void RenderDerived(UserID userID) const override;
        
      private:
        static constexpr float k_width {0.15f};
        static constexpr float k_height {0.12f};
    };
}