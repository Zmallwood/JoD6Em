/*
 * SceneManager.h
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
        
        void go_to(std::string_view scene_name);
        
    private:
        void add_scene(
            std::string_view scene_name,
            std::function<void()> update_action,
            std::function<void(boost::beast::websocket::stream<boost::asio::ip::
                                                               tcp::socket> &)>
            render_action,
            std::function<void()> key_down_action,
            std::function<void()> mouse_down_action);
        
        int m_current_scene = 0;
        
        std::map<int, scene> m_scenes;
        
        user_connection &m_user_connection;
    };
 }