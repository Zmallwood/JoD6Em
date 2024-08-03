/*
 * scene.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class scene {
    public:
        scene(
            std::function<void()> update_action,
            std::function<void(boost::beast::websocket::stream<boost::asio::ip::
                                                               tcp::socket> &)>
            render_action,
            std::function<void()> key_down_action,
            std::function<void()> mouse_down_action);
        
        void update();
        
        void render(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        
        void on_mouse_down();
        
        void on_key_down();
        
    private:
        std::function<void()> m_update_action;
        
        std::function<void(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &)>
        m_render_action;
        
        std::function<void()> m_key_down_action;
        
        std::function<void()> m_mouse_down_action;
    };
}