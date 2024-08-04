/*
 * IMainSceneComponent.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class MainScene;
    class UserConnection;
    
    class IMainSceneComponent {
      public:
        IMainSceneComponent(UserConnection& userConnection,
                            MainScene& mainScene);
        
        virtual void Update() {
        }
        
        virtual void Render(WebSocket &webSocket) const {
        }
        
      protected:
        UserConnection &m_userConnection;
        MainScene& m_mainScene;
    };
}