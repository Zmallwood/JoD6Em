/*
 * GUILabel.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "GUIComponent.hpp"

namespace JoD {
    
    class GUILabel : public GUIComponent {
        
      public:
        GUILabel(PointF position, std::string_view text);
        
        void Render(WebSocket& webSocket) override;
        
      private:
        std::string m_text;
    };
}