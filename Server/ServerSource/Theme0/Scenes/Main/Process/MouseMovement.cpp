/*
 * MouseMovement.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseMovement.hpp"
#include "ServerCore/Net/UserConnection.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "TileHovering.hpp"
#include "MobTargeting.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"

namespace JoD {
    
    void MouseMovement::Update(){
        
        auto &mainScene = *EngineInstance().SceneManager()->GetScene<MainScene>("MainScene");
        
        const std::shared_ptr<const TileHovering> tileHovering =
            std::static_pointer_cast<TileHovering>(
                mainScene.m_components.at(
                    MainSceneComponents::
                    TileHovering));
                    
        const std::shared_ptr<MobTargeting> mobTargeting =
            std::static_pointer_cast<MobTargeting>(
                mainScene.m_components.at(
                    MainSceneComponents::
                    MobTargeting));
        
        const auto mouseDown =
            EngineInstance().MouseInput()->
            LeftButton()->
            IsPressedPickResult();
        
        auto &player = EngineInstance().Player();
        
        const auto hoveredTile =
            tileHovering->m_hoveredCoordinate;
        
        if (mouseDown) {
            
            player->SetDestCoord(hoveredTile);
            mobTargeting->m_targetedCreature = nullptr;
        }
        
        if (std::chrono::high_resolution_clock::now() >
            player->TicksLastMove() +
            std::chrono::high_resolution_clock::duration(
                std::chrono::milliseconds(
                    static_cast<int>(1000/
                                     player->
                                     MovementSpeed())))){
            
            if (player->DestCoord().has_value()){
                
                const auto dx = player->DestCoord()->x - player->Coord().x;
                const auto dy = player->DestCoord()->y - player->Coord().y;
                
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
                    
                    player->SetTicksLastMove(Now());
                } else  {
                    
                    player->SetDestCoord(std::nullopt);
                }
            }
        }
    }
}