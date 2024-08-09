/*
 * GUIPanel.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "GUIComponent.hpp"

namespace JoD {
    
    class GUIPanel : public GUIComponent {
      public:
        GUIPanel(BoxF bounds);
        
        void RenderDerived(UserID userID, WebSocket& webSocket) const override;
        
      private:
        BoxF GetBounds() const;
      
        SizeF m_size;
    };
}