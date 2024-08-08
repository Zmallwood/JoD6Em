/*
 * IMainSceneComponent.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IMainSceneComponent.hpp"

namespace JoD {
    
    IMainSceneComponent::IMainSceneComponent(const UserGameInstanceEngine& userGameInstanceEngine,
                                             const MainScene& mainScene)
        : m_userGameInstanceEngine(userGameInstanceEngine), m_mainScene(mainScene){
        
    }
}