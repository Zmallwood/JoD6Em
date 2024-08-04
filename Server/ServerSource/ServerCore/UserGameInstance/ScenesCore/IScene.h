/*
 * IScene.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserConnection;
    
    class IScene {
    public:
        IScene(UserConnection& user_connection);
        
        void Update();
        
        void Render(WebSocket &webSocket);
        
    protected:
        virtual void UpdateDerived() = 0;
        
        virtual void RenderDerived(WebSocket
                                   &webSocket) = 0;
        
        UserConnection &m_user_connection;
    };
}