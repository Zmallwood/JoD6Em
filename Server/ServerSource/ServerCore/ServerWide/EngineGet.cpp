/*
 * EngineInstancesManager.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "EngineGet.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"

namespace JoD {
    
    struct EngineGet::Impl {
        std::map<UserID, std::unique_ptr<EngineInstance>> engineInstances;
    };
    
    EngineGet::EngineGet() : m_pImpl(std::make_unique<Impl>()) {
        
    }
    
    EngineGet::~EngineGet() {
        
    }
    
    UserID EngineGet::RegisterEngineInstance() {
        
        auto userID = s_currentUserID++;
        
        m_pImpl->engineInstances.insert({userID, std::make_unique<EngineInstance>(userID)});
        
        return userID;
    }
    
    EngineInstance* EngineGet::GetInstance(UserID userID) const {
        
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID).get();
        }
        
        return nullptr;
    }
    
    std::optional<PointF> EngineGet::GetMousePosition(UserID userID) const {
        
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->MousePosition();
        }
        
        return std::nullopt;
    }
        
    std::optional<float> EngineGet::GetAspectRatio(UserID userID) const {
        
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->GetAspectRatio();
        }
        
        return std::nullopt;
    }
    
    Player* EngineGet::GetPlayer(UserID userID) const {
        
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->Player();
        }
        
        return nullptr;
    }
    
    SceneManager* EngineGet::GetSceneManager(UserID userID) const {
        
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->SceneManager();
        }
        
        return nullptr;
    }
    
    MouseInput* EngineGet::GetMouseInput(UserID userID) const {
        
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->MouseInput();
        }
        
        return nullptr;
    }
    
    TextMessages* EngineGet::GetTextMessages(UserID userID) const {
        
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->TextMessages();
        }
        
        return nullptr;
    }
}