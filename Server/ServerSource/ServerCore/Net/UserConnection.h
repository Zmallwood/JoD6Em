/*
 * UserConnection.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class UserGameInstanceEngine;
    class Player;
    class TileHovering;
    class MouseMovement;
    class Cursor;
    class MobTargeting;
    class WorldView;
    
    class UserConnection {
    public:
        UserConnection(boost::asio::ip::tcp::socket socket);
        
        void
        SendImageDrawInstruction(WebSocket &ws,
                                 std::string_view image_name,
                                 RectF destination);
        
        void
        SendImageDrawInstruction(WebSocket &ws,
                                 int image_name_hash,
                                 RectF destination);
        
        void SendTextDrawInstruction(WebSocket &ws,
                                     std::string_view text, PointF position);
        
        void SendPresentCanvasInstruction(WebSocket &ws);
        
        float GetAspectRatio();
        
        std::shared_ptr<Player> m_player;
        
        std::shared_ptr<TileHovering> m_tile_hovering;
        
        std::shared_ptr<MouseMovement> m_mouse_movement;
        
        std::shared_ptr<MobTargeting> m_mob_targeting;

        std::shared_ptr<WorldView> m_worldView;
        
        PointF m_mouse_position;
        
        std::shared_ptr<UserGameInstanceEngine> m_user_game_instance_engine;
        
        std::shared_ptr<Cursor> m_cursor;
        
    private:
        void DoSession(boost::asio::ip::tcp::socket socket);
        
        Size m_canvas_size;
    };
}