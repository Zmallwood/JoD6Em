// Copyright (c) 2024 Andreas Åkerberg.

#include "ClientCore.h"

#include "Client.h"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace jod
{
    ServerEngine::ServerEngine(Client &client)
        : m_client(client), m_sceneManager(std::make_shared<SceneManager>(client))
    {
    }

    void ServerEngine::Update()
    {
        m_sceneManager->UpdateCurrentScene();
    }

    void ServerEngine::Render(websocket::stream<tcp::socket> &ws)
    {
        m_sceneManager->RenderCurrentScene(ws);
    }

    void ServerEngine::OnKeyDown()
    {
        m_sceneManager->OnKeyDownCurrentScene();
    }

    void ServerEngine::OnMouseDown()
    {
        m_sceneManager->OnMouseDownCurrentScene();
    }

    Scene::Scene(std::function<void()> updateAction,
                 std::function<void(websocket::stream<tcp::socket> &)> renderAction,
                 std::function<void()> keyDownAction, std::function<void()> mouseDownAction)
        : m_updateAction(updateAction), m_renderAction(renderAction),
          m_keyDownAction(keyDownAction), m_mouseDownAction(mouseDownAction)
    {
    }

    void Scene::Update()
    {
        m_updateAction();
    }

    void Scene::Render(websocket::stream<tcp::socket> &ws)
    {
        m_renderAction(ws);
    }

    void Scene::OnKeyDown()
    {
        m_keyDownAction();
    }

    void Scene::OnMouseDown()
    {
        m_mouseDownAction();
    }

    SceneManager::SceneManager(Client &client) : m_client(client)
    {
        AddScene(
            "IntroScene", [] {},
            [&](websocket::stream<tcp::socket> &ws)
            {
                m_client.SendImageDrawInstruction(ws, "DefaultSceneBackground",
                                                  {0.0f, 0.0f, 1.0f, 1.0f});
                m_client.SendImageDrawInstruction(ws, "JoDLogo", {0.3f, 0.2f, 0.4f, 0.2f});
                m_client.SendPresentCanvasInstruction(ws);
            },
            [] {}, [&] { this->GoTo("MainMenuScene"); });

        AddScene(
            "MainMenuScene", [] {},
            [&](websocket::stream<tcp::socket> &ws)
            {
                m_client.SendImageDrawInstruction(ws, "DefaultSceneBackground",
                                                  {0.0f, 0.0f, 1.0f, 1.0f});
                m_client.SendImageDrawInstruction(ws, "JoDLogo", {0.4f, 0.1f, 0.2f, 0.1f});
                m_client.SendPresentCanvasInstruction(ws);
            },
            [] {}, [] {});

        GoTo("IntroScene");
    }

    void SceneManager::UpdateCurrentScene()
    {
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).Update();
    }

    void SceneManager::RenderCurrentScene(websocket::stream<tcp::socket> &ws)
    {
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).Render(ws);
    }

    void SceneManager::OnKeyDownCurrentScene()
    {
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).OnKeyDown();
    }

    void SceneManager::OnMouseDownCurrentScene()
    {
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).OnMouseDown();
    }

    void SceneManager::GoTo(std::string_view sceneName)
    {
        m_currentScene = Hash(sceneName);
    }

    void SceneManager::AddScene(std::string_view sceneName, std::function<void()> updateAction,
                                std::function<void(websocket::stream<tcp::socket> &)> renderAction,
                                std::function<void()> keyDownAction,
                                std::function<void()> mouseDownAction)
    {
        m_scenes.insert(
            {Hash(sceneName), {updateAction, renderAction, keyDownAction, mouseDownAction}});
    }
}