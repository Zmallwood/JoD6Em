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
        
        void Update(UserID userID);
        
        void Render(UserID userID) const;
        
        virtual void UpdateDerived(UserID userID) {
            
        }
        
        virtual void RenderDerived(UserID userID) const {
            
        }
        
        void SetVisible(bool value) {
            
            m_visible = value;
        }
        
      protected:
        PointF m_position;
        bool m_visible {true};
    };
}