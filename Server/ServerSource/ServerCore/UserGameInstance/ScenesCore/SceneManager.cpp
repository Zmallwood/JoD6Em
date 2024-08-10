/*
 * SceneManager.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "SceneManager.hpp"
#include "Theme0/Scenes/Intro/IntroScene.hpp"
#include "Theme0/Scenes/MainMenu/MainMenuScene.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"

namespace JoD {
    
    struct SceneManager::Impl {
        int currentScene {0}; ///< Hash code of name of the currently presented scene.
        std::map<int, std::unique_ptr<IScene>> scenes; ///< All scenes that has been added in ctor.
    };
    
    SceneManager::SceneManager(
        UserID userID, EngineInstance &engineInstance) : m_pImpl(std::make_unique<Impl>()){
            
        AddScene(userID, "IntroScene", std::make_unique<IntroScene>());
        
        AddScene(userID,
            "MainMenuScene",
            std::make_unique<MainMenuScene>());
        
        AddScene(userID, "MainScene", std::make_unique<MainScene>());
        
        GoToScene(userID, "IntroScene");
    }
    
    SceneManager::~SceneManager() {
        
    }
    
    void SceneManager::AddScene(
        UserID userID,
        std::string_view sceneName,
        std::unique_ptr<IScene> scene) {
        
        scene->Initialize(userID);
        
        m_pImpl->scenes.insert({Hash(sceneName), std::move(scene)});
    }
    
    std::map<int, std::unique_ptr<IScene>> &SceneManager::GetScenes() const {
        
        return m_pImpl->scenes;
    }
    
    void SceneManager::UpdateCurrentScene(UserID userID) {
        
        if (m_pImpl->scenes.contains(m_pImpl->currentScene)) {
            
            m_pImpl->scenes.at(m_pImpl->currentScene)->Update(userID);
        }
    }
    
    void SceneManager::RenderCurrentScene(UserID userID, WebSocket &webSocket) const {
        
        if (m_pImpl->scenes.contains(m_pImpl->currentScene)) {
            
            m_pImpl->scenes.at(m_pImpl->currentScene)->Render(userID, webSocket);
        }
    }
    
    void SceneManager::GoToScene(UserID userID, std::string_view scene_name) {
        
        m_pImpl->currentScene = Hash(scene_name);
        
        if (m_pImpl->scenes.contains(m_pImpl->currentScene)) {
            
            m_pImpl->scenes.at(m_pImpl->currentScene)->OnEnter(userID);
        }
    }
}