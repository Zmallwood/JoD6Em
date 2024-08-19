/*
 * MouseMovement.cpp
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

void MouseMovement::Update(UserID userID) {
    
    auto &mainScene = *_<EngineGet>().GetSceneManager(userID)->GetScene<MainScene>("MainScene");
    
    auto tileHovering =
        static_cast<TileHovering*>(
            mainScene.GetComponent(
                MainSceneComponents::
                TileHovering));
    
    auto creatureTargeting =
        static_cast<CreatureTargeting*>(
            mainScene.GetComponent(
                MainSceneComponents::
                CreatureTargeting));
    
    const auto mouseDown =
        _<EngineGet>().GetMouseInput(userID)->
        GetLeftButton().
        GetIsPressedPickResult();
    
    auto player = _<EngineGet>().GetPlayer(userID);
    
    const auto hoveredTile =
        tileHovering->GetHoveredCoord();
    
    if (mouseDown && hoveredTile.has_value()) {
        
        player->SetDestCoord(hoveredTile.value());
        creatureTargeting->SetTargetedCreature(nullptr);
    }
    
    if (std::chrono::high_resolution_clock::now() >
        player->GetTimeLastMove() +
        std::chrono::high_resolution_clock::duration(
            std::chrono::milliseconds(
                static_cast<int>(1000/
                                 player->
                                 GetMoveSpd())))){
        
        if (player->GetDestCoord().has_value()){
            
            const auto dx = player->GetDestCoord()->x - player->GetCoord().x;
            const auto dy = player->GetDestCoord()->y - player->GetCoord().y;
            
            if (dx < 0 && dy < 0) {
                
                player->TryMove(userID, Directions::NorthWest);
            }
            else if (dx == 0 && dy < 0) {
                
                player->TryMove(userID, Directions::North);
            }
            else if (dx > 0 && dy < 0) {
                
                player->TryMove(userID, Directions::NorthEast);
            }
            else if (dx > 0 && dy == 0) {
                
                player->TryMove(userID, Directions::East);
            }
            else if (dx > 0 && dy > 0) {
                
                player->TryMove(userID, Directions::SouthEast);
            }
            else if (dx == 0 && dy > 0) {
                
                player->TryMove(userID, Directions::South);
            }
            else if (dx < 0 && dy > 0) {
                
                player->TryMove(userID, Directions::SouthWest);
            }
            else if (dx < 0 && dy == 0) {
                
                player->TryMove(userID, Directions::West);
            }
            
            if (dx || dy) {
                
                player->SetTimeLastMove(Now());
            }
            else {
                
                player->SetDestCoord(std::nullopt);
            }
        }
    }
}

}