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
#include "CreatureTargeting.hpp"
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
            static_cast<CreatureTargeting*>(
                mainScene.GetComponent(
                    MainSceneComponents::
                    MobTargeting));
        
        const auto mouseDown =
            _<EngineGet>().GetMouseInput(userID)->
            GetLeftButton().
            GetIsPressedPickResult();
        
        auto player = _<EngineGet>().GetPlayer(userID);
        
        const auto hoveredTile =
            tileHovering->GetHoveredCoordinate();
        
        if (mouseDown && hoveredTile.has_value()) {
            
            player->SetDestCoord(hoveredTile.value());
            mobTargeting->SetTargetedCreature(nullptr);
        }
        
        if (std::chrono::high_resolution_clock::now() >
            player->GetTicksLastMove() +
            std::chrono::high_resolution_clock::duration(
                std::chrono::milliseconds(
                    static_cast<int>(1000/
                                     player->
                                     GetMovementSpeed())))){
            
            if (player->GetDestCoord().has_value()){
                
                const auto dx = player->GetDestCoord()->x - player->GetCoord().x;
                const auto dy = player->GetDestCoord()->y - player->GetCoord().y;
                
                if (dx < 0 && dy < 0) {
                    
                    player->TryMoveNorthWest(userID);
                }
                else if (dx == 0 && dy < 0) {
                    
                    player->TryMoveNorth(userID);
                }
                else if (dx > 0 && dy < 0) {
                    
                    player->TryMoveNorthEast(userID);
                }
                else if (dx > 0 && dy == 0) {
                    
                    player->TryMoveEast(userID);
                }
                else if (dx > 0 && dy > 0) {
                    
                    player->TryMoveSouthEast(userID);
                }
                else if (dx == 0 && dy > 0) {
                    
                    player->TryMoveSouth(userID);
                }
                else if (dx < 0 && dy > 0) {
                    
                    player->TryMoveSouthWest(userID);
                }
                else if (dx < 0 && dy == 0) {
                    
                    player->TryMoveWest(userID);
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