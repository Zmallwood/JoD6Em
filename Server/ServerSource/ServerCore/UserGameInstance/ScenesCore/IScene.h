/*
 * IScene.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class user_connection;
    
    class IScene {
    public:
        IScene(user_connection& user_connection);
        
        void Update();
        
        void Render(WebSocket &webSocket);
        
    protected:
        virtual void UpdateDerived() = 0;
        
        virtual void RenderDerived(WebSocket
                                   &webSocket) = 0;
        
        user_connection &m_user_connection;
    };
}