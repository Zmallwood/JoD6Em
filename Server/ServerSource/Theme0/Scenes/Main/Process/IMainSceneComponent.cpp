/*
 * IMainSceneComponent.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IMainSceneComponent.hpp"

namespace JoD {
    
    IMainSceneComponent::IMainSceneComponent(const EngineInstance& engineInstance,
                                             const MainScene& mainScene)
        : m_engineInstance(engineInstance), m_mainScene(mainScene){
        
    }
}