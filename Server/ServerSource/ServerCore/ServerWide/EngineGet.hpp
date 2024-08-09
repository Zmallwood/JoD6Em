/*
 * EngineInstancesManager.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/EngineInstance.hpp"

namespace JoD {
    
    class Player;
    class SceneManager;
    class MouseInput;
    class TextMessages;
    
    class EngineGet {
      public:
        UserID RegisterEngineInstance();
        
        EngineInstance* GetInstance(UserID userID) const;

        std::optional<PointF> GetMousePosition(UserID userID) const;
        
        std::optional<float> GetAspectRatio(UserID userID) const;
        
        Player* GetPlayer(UserID userID) const;
        
        SceneManager* GetSceneManager(UserID userID) const;
        
        MouseInput* GetMouseInput(UserID userID) const;
        
        TextMessages* GetTextMessages(UserID userID) const;
        
      private:
        std::map<UserID, std::unique_ptr<EngineInstance>> m_engineInstances;
        inline static UserID s_currentUserID {0};
    };
}