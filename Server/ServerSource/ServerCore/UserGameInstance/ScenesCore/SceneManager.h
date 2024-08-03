/*
 * SceneManager.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class user_connection;
    class IScene;

    class scene_manager {
    public:
        scene_manager(user_connection &user_connection);
        
        void update_current_scene();
        
        void render_current_scene(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        
        void go_to(std::string_view scene_name);
        
    private:
        int m_current_scene = 0;
        
        std::map<int, std::shared_ptr<IScene>> m_scenes;
        
        user_connection &m_user_connection;
    };
 }