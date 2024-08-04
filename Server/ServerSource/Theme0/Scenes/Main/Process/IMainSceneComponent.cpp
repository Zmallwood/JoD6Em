/*
 * IMainSceneComponent.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "IMainSceneComponent.hpp"

namespace JoD {
    IMainSceneComponent::IMainSceneComponent(UserConnection& userConnection,
                                             MainScene& mainScene)
        : m_userConnection(userConnection), m_mainScene(mainScene){
    }
}