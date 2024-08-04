/*
 * UserConnection.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserGameInstanceEngine;
    class Player;
    class Cursor;
    
    class UserConnection {
    public:
        UserConnection(boost::asio::ip::tcp::socket socket);
        
        void SendImageDrawInstruction(
            WebSocket &ws,
            std::string_view imageName,
            RectF destination) const;
        
        void SendImageDrawInstruction(
            WebSocket &ws,
            int imageNamehash,
            RectF destination) const;
        
        void SendTextDrawInstruction(
            WebSocket &ws,
            std::string_view text, PointF position) const;
        
        void SendPresentCanvasInstruction(WebSocket &ws) const;
        
        float GetAspectRatio() const;
        
        std::shared_ptr<Player> m_player;
        
        PointF m_mousePosition;
        
        std::shared_ptr<UserGameInstanceEngine> m_userGameInstanceEngine;
        
        std::shared_ptr<Cursor> m_cursor;
        
    private:
        void DoSession(boost::asio::ip::tcp::socket socket);
        
        Size m_canvasSize;
    };
}