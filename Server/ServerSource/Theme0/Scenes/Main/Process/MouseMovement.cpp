/*
 * MouseMovement.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "MouseMovement.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseButton.hpp"
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "TileHovering.hpp"
#include "MobTargeting.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "ServerCore/UserGameInstance/ScenesCore/SceneManager.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {
    
    void MouseMovement::Update(UserID userID){
        
        auto &mainScene = *_<EngineGet>().GetSceneManager(userID)->GetScene<MainScene>("MainScene");
        
        auto tileHovering =
            static_cast<TileHovering*>(
                mainScene.GetComponent(
                    MainSceneComponents::
                    TileHovering));
                    
        auto mobTargeting =
            static_cast<MobTargeting*>(
                mainScene.GetComponent(
                    MainSceneComponents::
                    MobTargeting));
        
        const auto mouseDown =
            _<EngineGet>().GetMouseInput(userID)->
            LeftButton().
            IsPressedPickResult();
        
        auto player = _<EngineGet>().GetPlayer(userID);
        
        const auto hoveredTile =
            tileHovering->HoveredCoordinate();
        
        if (mouseDown && hoveredTile.has_value()) {
            
            player->SetDestCoord(hoveredTile.value());
            mobTargeting->SetTargetedCreature(nullptr);
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