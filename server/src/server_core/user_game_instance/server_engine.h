/*
 * server_engine.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class user_connection;
    class mouse_input;
    class scene_manager;
    class fps_counter;

    class server_engine {
    public:
        server_engine(user_connection &user_connection);
        
        void update();
        
        void render(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        
        void on_mouse_down();
        
        void on_key_down();
        
        std::shared_ptr<mouse_input> m_mouse_input;
        
    private:
        std::shared_ptr<scene_manager> m_scene_manager;

        std::shared_ptr<fps_counter> m_fps_counter;
        
        user_connection &m_user_connection;
    };
}