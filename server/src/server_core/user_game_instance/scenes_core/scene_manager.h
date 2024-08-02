/*
 * scene_manager.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class user_connection;
    class scene;

    class scene_manager {
    public:
        scene_manager(user_connection &user_connection);
        
        void update_current_scene();
        
        void render_current_scene(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        
        void on_mouse_down_current_scene();
        
        void on_key_down_current_scene();
        
        void go_to(std::string_view sceneName);
        
    private:
        void add_scene(
            std::string_view sceneName,
            std::function<void()> updateAction,
            std::function<void(boost::beast::websocket::stream<boost::asio::ip::
                                                               tcp::socket> &)>
            renderAction,
            std::function<void()> keyDownAction,
            std::function<void()> mouseDownAction);
        
        int m_currentScene = 0;
        
        std::map<int, scene> m_scenes;
        
        user_connection &m_user_connection;
    };
 }