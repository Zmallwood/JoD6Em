/*
 * UserConnection.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class server_engine;
    class player;
    class tile_hovering;
    class mouse_movement;
    class cursor;
    class mob_targeting;
    
    class user_connection {
    public:
        user_connection(boost::asio::ip::tcp::socket socket);
        
        void
        send_image_draw_instruction(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws,
            std::string_view image_name,
            rectf destination);
        
        void
        send_image_draw_instruction(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws,
            int image_name_hash,
            rectf destination);
        
        void send_text_draw_instruction(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws,
            std::string_view text, pointf position);
        
        void send_present_canvas_instruction(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        
        float get_aspect_ratio();
        
        std::shared_ptr<player> m_player;
        
        std::shared_ptr<tile_hovering> m_tile_hovering;
        
        std::shared_ptr<mouse_movement> m_mouse_movement;

        std::shared_ptr<mob_targeting> m_mob_targeting;
        
        pointf m_mouse_position;
        
        std::shared_ptr<server_engine> m_server_engine;
        
        std::shared_ptr<cursor> m_cursor;
        
    private:
        void do_session(boost::asio::ip::tcp::socket socket);
        
        size m_canvas_size;
    };
}