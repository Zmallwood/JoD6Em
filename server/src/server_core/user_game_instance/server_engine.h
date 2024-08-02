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

    class server_engine {
    public:
        server_engine(user_connection &user_connection);
        
        void update();
        
        void render(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        
        void on_mouse_down();
        
        void on_key_down();
        
        std::shared_ptr<mouse_input> m_mouseInput;
        
    private:
        std::shared_ptr<scene_manager> m_sceneManager;
        
        user_connection &m_user_connection;
    };
}