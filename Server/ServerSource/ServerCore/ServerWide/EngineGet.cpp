/*
 * EngineInstancesManager.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "EngineGet.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"

namespace JoD {
    
    // PIMPL idiom to reduce header includes.
    struct EngineGet::Impl {
        
        std::map<UserID, std::unique_ptr<EngineInstance>> engineInstances; // Engine isntances for all connected users.
        
        inline static UserID s_currentUserID {1};                          // Note: IDs start at 1 so 0 can be used for unspecified/lacking IDs.
    };
    
    EngineGet::EngineGet() : m_pImpl(std::make_unique<Impl>()) {}
    
    EngineGet::~EngineGet() {}
    
    UserID EngineGet::CreateNewEngineInstance(Socket socket) {
        
        // Get an unique ID for the user, and icrease the global counter.
        auto userID = Impl::s_currentUserID++;
        
        // Create the actual EngineInstance with the provided socket and store it.
        m_pImpl->engineInstances.insert(
            {userID,
             std::make_unique<EngineInstance>(
                 userID, std::move(socket))});
        
        // Return the user ID so it can be used else where to access engine components later.
        return userID;
    }
    
    EngineInstance* EngineGet::GetEngineInstance(UserID userID) const {
        
        // Return EngineInstance if valid user ID, otherwise return fail result.
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID).get();
        }
        
        return nullptr;
    }
    
    std::optional<PointF> EngineGet::GetMousePosition(UserID userID) const {
        
        // Return mouse position if valid user ID, otherwise return fail result.
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->GetMousePosition();
        }
        
        return std::nullopt;
    }
    
    std::optional<float> EngineGet::GetAspectRatio(UserID userID) const {
        
        // Return aspect ratio if valid user ID, otherwise return fail result.
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->GetAspectRatio();
        }
        
        return std::nullopt;
    }
    
    Player* EngineGet::GetPlayer(UserID userID) const {
        
        // Return Player if valid user ID, otherwise return fail result.
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->GetPlayer();
        }
        
        return nullptr;
    }
    
    SceneManager* EngineGet::GetSceneManager(UserID userID) const {
        
        // Return SceneManager if valid user ID, otherwise return fail result.
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->GetSceneManager();
        }
        
        return nullptr;
    }
    
    MouseInput* EngineGet::GetMouseInput(UserID userID) const {
        
        // Return MouseInput if valid user ID, otherwise return fail result.
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->GetMouseInput();
        }
        
        return nullptr;
    }
    
    TextMessages* EngineGet::GetTextMessages(UserID userID) const {
        
        // Return TextMessages if valid user ID, otherwise return fail result.
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->GetTextMessages();
        }
        
        return nullptr;
    }
    
    WebSocket *EngineGet::GetWebSocket(UserID userID) const {
        
        // Return WebSocket if valid user ID, otherwise return fail result.
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->GetWebSocket();
        }
        
        return nullptr;
    }
    
    Cursor *EngineGet::GetCursor(UserID userID) const {
        
        if (m_pImpl->engineInstances.contains(userID)) {
            
            return m_pImpl->engineInstances.at(userID)->GetCursor();
        }
        
        return nullptr;
    }
}