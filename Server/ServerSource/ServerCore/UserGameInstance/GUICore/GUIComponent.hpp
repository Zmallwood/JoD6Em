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
        
        void Update();
        
        void Render(WebSocket &webSocket);
        
        virtual void UpdateDerived() {
            
        }
        
        virtual void RenderDerived(WebSocket &webSocket) {
            
        }
        
        void SetVisible(bool value) {
            
            m_visible = value;
        }
        
      protected:
        PointF m_position;
        bool m_visible {true};
    };
}