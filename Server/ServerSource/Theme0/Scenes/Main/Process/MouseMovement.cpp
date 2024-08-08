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
#include "MobTargeting.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"

namespace JoD {
    
    void MouseMovement::Update(){
        
        const std::shared_ptr<const TileHovering> tileHovering =
            std::static_pointer_cast<TileHovering>(
                m_mainScene.m_components.at(
                    MainSceneComponents::
                    TileHovering));
                    
        const std::shared_ptr<MobTargeting> mobTargeting =
            std::static_pointer_cast<MobTargeting>(
                m_mainScene.m_components.at(
                    MainSceneComponents::
                    MobTargeting));
        
        const auto mouseDown =
            m_userGameInstanceEngine.m_mouseInput->
            m_leftButton->
            IsPressedPickResult();
        
        auto player = m_userGameInstanceEngine.m_player;
        
        const auto hoveredTile =
            tileHovering->m_hoveredCoordinate;
        
        if (mouseDown) {
            
            player->m_destCoord = hoveredTile;
            mobTargeting->m_targetedCreature = nullptr;
        }
        
        if (std::chrono::high_resolution_clock::now() >
            player->m_ticksLastMove +
            std::chrono::high_resolution_clock::duration(
                std::chrono::milliseconds(
                    static_cast<int>(1000/
                                     player->
                                     m_movementSpeed)))){
            
            if (player->m_destCoord.has_value()){
                
                const auto dx = player->m_destCoord->x - player->m_coord.x;
                const auto dy = player->m_destCoord->y - player->m_coord.y;
                
                if (dx < 0 && dy < 0) {
                    
                    player->TryMoveNorthWest();
                }
                else if (dx == 0 && dy < 0) {
                    
                    player->TryMoveNorth();
                }
                else if (dx > 0 && dy < 0) {
                    
                    player->TryMoveNorthEast();
                }
                else if (dx > 0 && dy == 0) {
                    
                    player->TryMoveEast();
                }
                else if (dx > 0 && dy > 0) {
                    
                    player->TryMoveSouthEast();
                }
                else if (dx == 0 && dy > 0) {
                    
                    player->TryMoveSouth();
                }
                else if (dx < 0 && dy > 0) {
                    
                    player->TryMoveSouthWest();
                }
                else if (dx < 0 && dy == 0) {
                    
                    player->TryMoveWest();
                }
                
                if (dx || dy) {
                    
                    player->m_ticksLastMove = Now();
                } else  {
                    
                    player->m_destCoord = std::nullopt;
                }
            }
        }
    }
}