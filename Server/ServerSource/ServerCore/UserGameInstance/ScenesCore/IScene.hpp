/*
 * IScene.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class UserConnection;
    
    class IScene {
        
      public:
        IScene(UserConnection& userConnection);
        
        virtual void Initialize() {
        }
        
        void Update();
        
        void Render(WebSocket &webSocket) const;
        
      protected:
        virtual void UpdateDerived() = 0;
        
        virtual void RenderDerived(
            WebSocket
            &webSocket) const = 0;
        
        UserConnection &m_userConnection;
    };
}