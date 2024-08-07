/*
 * GUIComponent.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class GUIComponent {
        
      public:
        GUIComponent(PointF position);
      
        virtual void Update() {
        }
        
        virtual void Render(WebSocket &webSocket) {
        }
        
      protected:
        PointF m_position;
    };
}