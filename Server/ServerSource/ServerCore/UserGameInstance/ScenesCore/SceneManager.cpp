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
        
        int currentScene {0}; // Hash code of name of the currently presented scene.
        
        std::map<int, std::unique_ptr<IScene>>
        scenes;               // All scenes that has been added in ctor.
    };
    
    SceneManager::SceneManager(UserID userID) : m_pImpl(std::make_unique<Impl>()) {
        
        // Add intro scene.
        AddScene(userID, "IntroScene", std::make_unique<IntroScene>());
        
        // Add main menu scene.
        AddScene(
            userID,
            "MainMenuScene",
            std::make_unique<MainMenuScene>());
        
        // Add main scene.
        AddScene(userID, "MainScene", std::make_unique<MainScene>());
        
        // Set starting scene to intro scene.
        GoToScene(userID, "IntroScene");
    }
    
    SceneManager::~SceneManager() {}
    
    void SceneManager::AddScene(
        UserID userID,
        std::string_view sceneName,
        std::unique_ptr<IScene> scene) {
        
        // Initialize scene.
        scene->Initialize(userID);
        
        // And store it by the hash code of the scene name as key.
        m_pImpl->scenes.insert({Hash(sceneName), std::move(scene)});
    }
    
    std::map<int, std::unique_ptr<IScene>> &SceneManager::GetScenes() const {
        
        // Return reference to the scenes storage.
        return m_pImpl->scenes;
    }
    
    void SceneManager::UpdateCurrentScene(UserID userID) {
        
        // If scene exists...
        if (m_pImpl->scenes.contains(m_pImpl->currentScene)) {
            
            // Update it.
            m_pImpl->scenes.at(m_pImpl->currentScene)->Update(userID);
        }
    }
    
    void SceneManager::RenderCurrentScene(UserID userID) const {
        
        // If scene exists...
        if (m_pImpl->scenes.contains(m_pImpl->currentScene)) {
            
            // Render it.
            m_pImpl->scenes.at(m_pImpl->currentScene)->Render(userID);
        }
    }
    
    void SceneManager::GoToScene(UserID userID, std::string_view scene_name) {
        
        // Update the current scene to the new one.
        m_pImpl->currentScene = Hash(scene_name);
        
        // If the new scene exists...
        if (m_pImpl->scenes.contains(m_pImpl->currentScene)) {
            
            // Call its OnEnter() function.
            m_pImpl->scenes.at(m_pImpl->currentScene)->OnEnter(userID);
        }
    }
}