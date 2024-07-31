// Copyright (c) 2024 Andreas Åkerberg.
#include "ClientCore.h"
#include "Client.h"
#include "Math.h"
#include "Configuration.h"
#include "Player.h"
#include "World.h"
#include "SceneComponents.h"
#include "Cursor.h"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace jod {
    ServerEngine::ServerEngine(Client &client)
        : m_client(client), m_sceneManager(std::make_shared<SceneManager>(client)),
        m_mouseInput(std::make_shared<MouseInput>()){
    }
    void
    ServerEngine::Update(){
        m_sceneManager->UpdateCurrentScene();
    }
    void
    ServerEngine::Render(websocket::stream<tcp::socket> &ws){
        m_sceneManager->RenderCurrentScene(ws);
        m_client.m_cursor->Render(ws);
        m_client.SendPresentCanvasInstruction(ws);
    }
    void
    ServerEngine::OnKeyDown(){
        m_sceneManager->OnKeyDownCurrentScene();
    }
    void
    ServerEngine::OnMouseDown(){
        m_sceneManager->OnMouseDownCurrentScene();
    }
    Scene::Scene(std::function<void()> updateAction,
                 std::function<void(websocket::stream<tcp::socket> &)> renderAction,
                 std::function<void()> keyDownAction, std::function<void()> mouseDownAction)
        : m_updateAction(updateAction), m_renderAction(renderAction),
        m_keyDownAction(keyDownAction), m_mouseDownAction(mouseDownAction){
    }
    void
    Scene::Update(){
        m_updateAction();
    }
    void
    Scene::Render(websocket::stream<tcp::socket> &ws){
        m_renderAction(ws);
    }
    void
    Scene::OnKeyDown(){
        m_keyDownAction();
    }
    void
    Scene::OnMouseDown(){
        m_mouseDownAction();
    }
    SceneManager::SceneManager(Client &client) : m_client(client){
        AddScene(
            "IntroScene", [] {
        },
            [&](websocket::stream<tcp::socket> &ws){
            m_client.SendImageDrawInstruction(ws, "DefaultSceneBackground",
                                              {0.0f, 0.0f, 1.0f, 1.0f});
            m_client.SendImageDrawInstruction(ws, "JoDLogo", {0.3f, 0.2f, 0.4f, 0.2f});
        },
            [] {
        }, [&] {
            this->GoTo("MainMenuScene");
        });
        AddScene(
            "MainMenuScene", [] {
        },
            [&](websocket::stream<tcp::socket> &ws){
            m_client.SendImageDrawInstruction(ws, "DefaultSceneBackground",
                                              {0.0f, 0.0f, 1.0f, 1.0f});
            m_client.SendImageDrawInstruction(ws, "JoDLogo", {0.4f, 0.1f, 0.2f, 0.1f});
        },
            [] {
        }, [&] {
            this->GoTo("MainScene");
        });
        AddScene(
            "MainScene",
            [&]{
            m_client.m_tileHovering->Update();
            m_client.m_mouseMovement->Update();
        },
            [&](websocket::stream<tcp::socket> &ws){
            auto tileSize = CalcTileSize(m_client.GetAspectRatio());
            auto playerCoord = m_client.m_player->m_coord;
            auto numGridRows = _<GameProperties>().numGridRows;
            auto numGridCols = numGridRows;
            for (auto y = 0; y < numGridRows; y++){
                for (auto x = 0; x < numGridCols; x++){
                    auto coordX = playerCoord.x - (numGridCols - 1) / 2 + x;
                    auto coordY = playerCoord.y - (numGridRows - 1) / 2 + y;
                    if (coordX < 0 || coordY < 0 || coordX >= 100 || coordY >= 100) continue;
                    auto tile = _<World>().m_currentWorldArea->m_tiles[coordX][coordY];
                    m_client.SendImageDrawInstruction(
                        ws, tile->m_ground,
                        {x * tileSize.w, y * tileSize.h, tileSize.w, tileSize.h});
                    if (coordX == m_client.m_tileHovering->m_hoveredCoordinate.x &&
                        coordY == m_client.m_tileHovering->m_hoveredCoordinate.y){
                        m_client.SendImageDrawInstruction(
                            ws, "HoveredTile",
                            {x * tileSize.w, y * tileSize.h, tileSize.w, tileSize.h});
                    }
                    if (coordX == playerCoord.x && coordY == playerCoord.y){
                        m_client.SendImageDrawInstruction(
                            ws, "Player",
                            {x * tileSize.w, y * tileSize.h, tileSize.w, tileSize.h});
                    }
                }
            }
        },
            [] {
        }, [] {
        });
        GoTo("IntroScene");
    }
    void
    SceneManager::UpdateCurrentScene(){
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).Update();
    }
    void
    SceneManager::RenderCurrentScene(websocket::stream<tcp::socket> &ws){
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).Render(ws);
    }
    void
    SceneManager::OnKeyDownCurrentScene(){
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).OnKeyDown();
    }
    void
    SceneManager::OnMouseDownCurrentScene(){
        if (m_scenes.contains(m_currentScene))
            m_scenes.at(m_currentScene).OnMouseDown();
    }
    void
    SceneManager::GoTo(std::string_view sceneName){
        m_currentScene = Hash(sceneName);
    }
    void
    SceneManager::AddScene(std::string_view sceneName, std::function<void()> updateAction,
                           std::function<void(websocket::stream<tcp::socket> &)> renderAction,
                           std::function<void()> keyDownAction,
                           std::function<void()> mouseDownAction){
        m_scenes.insert(
            {Hash(sceneName), {updateAction, renderAction, keyDownAction, mouseDownAction}});
    }
    MouseInput::MouseInput() : m_leftButton(std::make_shared<MouseButton>()){
    }
    void
    MouseInput::RegisterMouseDown(){
        m_leftButton->RegisterMouseDown();
    }
    void
    MouseButton::RegisterMouseDown(){
        m_isPressed = true;
    }
    bool
    MouseButton::IsPressedPickResult(){
        auto result = m_isPressed;
        m_isPressed = false;
        
        return result;
    }
}