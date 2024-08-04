/*
 * UserGameInstanceEngine.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */


#pragma once

namespace jod {
    class user_connection;
    class mouse_input;
    class scene_manager;
    class server_fps_counter;

    class user_game_instance_engine {
    public:
        user_game_instance_engine(user_connection &user_connection);
        
        void update();
        
        void render(WebSocket &ws);
        
        std::shared_ptr<mouse_input> m_mouse_input;
        
        std::shared_ptr<scene_manager> m_scene_manager;
        
    private:

        std::shared_ptr<server_fps_counter> m_server_fps_counter;
        
        user_connection &m_user_connection;
    };
}