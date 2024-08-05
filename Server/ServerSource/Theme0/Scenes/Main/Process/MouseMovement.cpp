/*
 * MouseMovement.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseMovement.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "TileHovering.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"

namespace JoD {
    
    void MouseMovement::Update(){
        
        auto tileHovering =
            std::static_pointer_cast<TileHovering>(
                m_mainScene.m_components.at(
                    MainSceneComponents::
                    TileHovering));
        
        auto mouseDown =
            m_userConnection.m_userGameInstanceEngine->m_mouseInput->
            m_leftButton->
            IsPressedPickResult();
        
        auto player = m_userConnection.m_player;
        
        auto hoveredTile =
            tileHovering->m_hoveredCoordinate;
        
        if (mouseDown) {
            
            player->m_destination = hoveredTile;
        }
        
        if (std::chrono::high_resolution_clock::now() >
            player->m_ticksLastMove +
            std::chrono::high_resolution_clock::duration(
                std::chrono::milliseconds(
                    static_cast<int>(1000/
                                     player->
                                     m_movementSpeed)))){
            
            if (player->m_destination.x != -1 && player->m_destination.y != -1){
                
                auto dx = player->m_destination.x - player->m_coordinate.x;
                auto dy = player->m_destination.y - player->m_coordinate.y;
                
                auto absDx = std::abs(dx);
                auto absDy = std::abs(dy);
                
                auto normX = 0;
                auto normY = 0;
                
                if (dx) {
                    
                    normX = dx / absDx;
                }
                
                if (dy) {
                    
                    normY = dy / absDy;
                }
                
                player->m_coordinate.x += normX;
                player->m_coordinate.y += normY;
            }
            
            player->m_ticksLastMove = Now();
        }
    }
}