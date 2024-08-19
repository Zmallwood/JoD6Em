/*
 * SceneManager.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class EngineInstance;
class IScene;

///
/// One instance is created for every connecting user. Initializes,
/// processes and navigates between all scenes used in the game.
///
class SceneManager {
    
  public:
    
    ///
    /// Construct a new Scene Manager object by initializing all scenes,
    /// and entering the IntroScene.
    ///
    /// @param userID User ID for which user the SceneManager belongs to.
    ///
    SceneManager(UserID userID);
    
    ///
    /// Destroy the SceneManager object, necessary for PIMPL idiom.
    ///
    ~SceneManager();
    
    ///
    /// Updates the scene currently being presented.
    ///
    /// @param userID User ID for which user the SceneManager belongs to.
    ///
    void UpdateCurrentScene(UserID userID);
    
    ///
    /// Renders the scene currently being presented.
    ///
    /// @param userID User ID for which user the SceneManager belongs to.
    ///
    void RenderCurrentScene(UserID userID) const;
    
    ///
    /// Move from the currently presented scene to another one.
    ///
    /// @param userID User ID for which user the SceneManager belongs to.
    /// @param sceneName Name of the scene to go to.
    ///
    void GoToScene(UserID userID, std::string_view sceneName);
    
    ///
    /// Get pointer to scene with specified name, casted to type T.
    ///
    /// @tparam T Type of scene to have the result casted to.
    /// @param sceneName Name of scene to retrieve.
    /// @return const T* Pointer to requested scene.
    ///
    template<class T>
    const T* GetScene(std::string_view sceneName) const {
        
        auto hashCode = Hash(sceneName);
        
        // If scene with the name exists...
        if (GetScenes().contains(hashCode)) {
            
            // Cast and return it.
            return static_cast<T*>(GetScenes().at(hashCode).get());
        }
        
        // Return nullptr if scene with the name doesnt exist.
        return nullptr;
    }
    
  private:
    
    ///
    /// Add a new scene, used in the ctor.
    ///
    /// @param userID User ID for which user the SceneManager belongs to.
    /// @param sceneName Name of the scene to add.
    /// @param scene The scene object to add.
    ///
    void AddScene(UserID userID, std::string_view sceneName,
                  std::unique_ptr<IScene> scene);
    
    ///
    /// Get a reference to collection of all the scenes.
    ///
    /// @return std::map<int, std::unique_ptr<IScene>>& Reference to scenes collection.
    ///
    std::map<int, std::unique_ptr<IScene>> &GetScenes() const;
    
    ///
    /// PIMPL idiom to reduce includes in header.
    ///
    struct Impl;
    
    std::unique_ptr<Impl> m_pImpl;     ///< PIMPL idiom.
};

}
