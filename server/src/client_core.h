// Copyright (c) 2024 Andreas Åkerberg.
#pragma once
namespace jod {
    class Client;
    class SceneManager;
    class KeyboardInput;
    class MouseInput;
    class MouseButton;
    class ServerEngine {
    public:
        ServerEngine(Client &client);
        void Update();
        void Render(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        void OnMouseDown();
        void OnKeyDown();
        
        std::shared_ptr<MouseInput> m_mouseInput;
    private:
        std::shared_ptr<SceneManager> m_sceneManager;
        Client &m_client;
    };
    class Scene {
    public:
        Scene(std::function<void()> updateAction,
              std::function<void(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &)>
              renderAction,
              std::function<void()> keyDownAction, std::function<void()> mouseDownAction);
        void Update();
        void Render(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        void OnMouseDown();
        void OnKeyDown();
    private:
        std::function<void()> m_updateAction;
        std::function<void(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &)>
        m_renderAction;
        std::function<void()> m_keyDownAction;
        std::function<void()> m_mouseDownAction;
    };
    class SceneManager {
    public:
        SceneManager(Client &client);
        void UpdateCurrentScene();
        void RenderCurrentScene(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        void OnMouseDownCurrentScene();
        void OnKeyDownCurrentScene();
        void GoTo(std::string_view sceneName);
    private:
        void AddScene(
            std::string_view sceneName, std::function<void()> updateAction,
            std::function<void(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &)>
            renderAction,
            std::function<void()> keyDownAction, std::function<void()> mouseDownAction);
        
        int m_currentScene = 0;
        std::map<int, Scene> m_scenes;
        Client &m_client;
    };
    class MouseInput {
    public:
        MouseInput();
        void RegisterMouseDown();
        std::shared_ptr<MouseButton> m_leftButton;
    };
    class MouseButton {
    public:
        void RegisterMouseDown();
        bool IsPressedPickResult();
        
        bool m_isPressed;
    };
}