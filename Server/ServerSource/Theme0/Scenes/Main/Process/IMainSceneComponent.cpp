/*
 * IMainSceneComponent.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IMainSceneComponent.hpp"

namespace JoD {
    
    IMainSceneComponent::IMainSceneComponent(const UserConnection& userConnection,
                                             const MainScene& mainScene)
        : m_userConnection(userConnection), m_mainScene(mainScene){
        
    }
}