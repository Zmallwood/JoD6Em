/*
 * EngineInstancesManager.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "EngineGet.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"

namespace JoD {
    
    UserID EngineGet::RegisterEngineInstance(EngineInstance&
                                                        engineInstance) {
        
        auto userID = s_currentUserID++;
        
        m_engineInstances.insert({userID, &engineInstance});
        
        return userID;
    }
    
    EngineInstance* EngineGet::GetInstance(UserID userID) const {
        
        if (m_engineInstances.contains(userID)) {
            
            return m_engineInstances.at(userID);
        }
        
        return nullptr;
    }
    
    std::optional<PointF> EngineGet::GetMousePosition(UserID userID) const {
        
        if (m_engineInstances.contains(userID)) {
            
            return m_engineInstances.at(userID)->MousePosition();
        }
        
        return std::nullopt;
    }
        
    std::optional<float> EngineGet::GetAspectRatio(UserID userID) const {
        
        if (m_engineInstances.contains(userID)) {
            
            return m_engineInstances.at(userID)->GetAspectRatio();
        }
        
        return std::nullopt;
    }
    
    Player* EngineGet::GetPlayer(UserID userID) const {
        
        if (m_engineInstances.contains(userID)) {
            
            return m_engineInstances.at(userID)->Player();
        }
        
        return nullptr;
    }
    
    SceneManager* EngineGet::GetSceneManager(UserID userID) const {
        
        if (m_engineInstances.contains(userID)) {
            
            return m_engineInstances.at(userID)->SceneManager();
        }
        
        return nullptr;
    }
    
    MouseInput* EngineGet::GetMouseInput(UserID userID) const {
        
        if (m_engineInstances.contains(userID)) {
            
            return m_engineInstances.at(userID)->MouseInput();
        }
        
        return nullptr;
    }
}