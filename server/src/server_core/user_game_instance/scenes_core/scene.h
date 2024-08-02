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
            std::function<void()> updateAction,
            std::function<void(boost::beast::websocket::stream<boost::asio::ip::
                                                               tcp::socket> &)>
            renderAction,
            std::function<void()> keyDownAction,
            std::function<void()> mouseDownAction);
        
        void update();
        
        void render(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        
        void on_mouse_down();
        
        void on_key_down();
        
    private:
        std::function<void()> m_updateAction;
        
        std::function<void(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &)>
        m_renderAction;
        
        std::function<void()> m_keyDownAction;
        
        std::function<void()> m_mouseDownAction;
    };
}