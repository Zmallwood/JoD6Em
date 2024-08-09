/*
 * EngineInstancesManager.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "EngineInstancesManager.hpp"

namespace JoD {
    
    UserID EngineInstancesManager::RegisterEngineInstance(EngineInstance&
                                                        engineInstance) {
        
        auto userID = s_currentUserID++;
        
        m_engineInstances.insert({userID, &engineInstance});
        
        return userID;
    }
    
    EngineInstance* EngineInstancesManager::GetInstance(UserID userID) const {
        
        if (m_engineInstances.contains(userID)) {
            
            return m_engineInstances.at(userID);
        }
        
        return nullptr;
    }
}