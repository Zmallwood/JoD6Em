/*
 * EngineInstancesManager.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class EngineInstance;
    class Player;
    class SceneManager;
    class MouseInput;
    
    class EngineGet {
      public:
        UserID RegisterEngineInstance(EngineInstance& engineInstance);
        
        EngineInstance* GetInstance(UserID userID) const;

        std::optional<PointF> GetMousePosition(UserID userID) const;
        
        std::optional<float> GetAspectRatio(UserID userID) const;
        
        Player* GetPlayer(UserID userID) const;
        
        SceneManager* GetSceneManager(UserID userID) const;
        
        MouseInput* GetMouseInput(UserID userID) const;
        
      private:
        std::map<UserID, EngineInstance*> m_engineInstances;
        inline static UserID s_currentUserID {0};
    };
}