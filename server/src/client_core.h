// Copyright (c) 2024 Andreas Åkerberg.
#pragma once
namespace jod {
    class client;
    class scene_manager;
    class keyboard_input;
    class mouse_input;
    class mouse_button;
    class server_engine {
    public:
        server_engine(client &client);
        void update();
        void render(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        void on_mouse_down();
        void on_key_down();
        
        std::shared_ptr<mouse_input> m_mouseInput;
    private:
        std::shared_ptr<scene_manager> m_sceneManager;
        client &m_client;
    };
    class scene {
    public:
        scene(std::function<void()> updateAction,
              std::function<void(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &)>
              renderAction,
              std::function<void()> keyDownAction, std::function<void()> mouseDownAction);
        void update();
        void render(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        void on_mouse_down();
        void on_key_down();
    private:
        std::function<void()> m_updateAction;
        std::function<void(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &)>
        m_renderAction;
        std::function<void()> m_keyDownAction;
        std::function<void()> m_mouseDownAction;
    };
    class scene_manager {
    public:
        scene_manager(client &client);
        void update_current_scene();
        void render_current_scene(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        void on_mouse_down_current_scene();
        void on_key_down_current_scene();
        void go_to(std::string_view sceneName);
    private:
        void add_scene(
            std::string_view sceneName, std::function<void()> updateAction,
            std::function<void(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &)>
            renderAction,
            std::function<void()> keyDownAction, std::function<void()> mouseDownAction);
        
        int m_currentScene = 0;
        std::map<int, scene> m_scenes;
        client &m_client;
    };
    class mouse_input {
    public:
        mouse_input();
        void register_mouse_down();
        std::shared_ptr<mouse_button> m_leftButton;
    };
    class mouse_button {
    public:
        void register_mouse_down();
        bool is_pressed_pick_result();
        
        bool m_isPressed;
    };
}