// client.h
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
///////////////////////////////////////////////////////////

#pragma once

namespace jod {
    class server_engine;
    class player;
    class tile_hovering;
    class mouse_movement;
    class cursor;
    
    class client {
    public:
        client(boost::asio::ip::tcp::socket socket);
        
        void
        send_image_draw_instruction(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws,
            std::string_view imageName,
            rectf dest);
        
        void
        send_image_draw_instruction(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws,
            int imageNameHash,
            rectf dest);
        
        void send_present_canvas_instruction(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        
        float get_aspect_ratio();
        
        std::shared_ptr<player> m_player;
        
        std::shared_ptr<tile_hovering> m_tileHovering;
        
        std::shared_ptr<mouse_movement> m_mouseMovement;
        
        pointf m_mousePosition;
        
        std::shared_ptr<server_engine> m_serverEngine;
        
        std::shared_ptr<cursor> m_cursor;
        
    private:
        void do_session(boost::asio::ip::tcp::socket socket);
        
        size m_canvasSize;
    };
}