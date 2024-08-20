/*
 * ObjectHovering.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ObjectHovering.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"
#include "ObjectsPile.hpp"
#include "Object.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"
#include "TileHovering.hpp"
#include "MainSceneComponents.hpp"
#include "Theme0/Scenes/Main/MainScene.hpp"
#include "Configuration/ObjectsIndex.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"

namespace JoD {
void ObjectHovering::Update(UserID userID) {
    
    auto &mainScene = *_<EngineGet>().GetMainScene(userID);
    auto tileHov =
        static_cast<TileHovering*>(mainScene.GetComponent(
                                       MainSceneComponents::TileHovering));
    auto hovTile = tileHov->GetHoveredCoord();
    auto wArea = _<World>().GetCurrWorldArea();
    
    auto tile = wArea->GetTile(hovTile.value());
    
    auto &objectsPile = tile->GetObjectsPile();
    
    
    m_objectHoverTextLines.clear();
    
    for (auto object : objectsPile.GetObjects()) {
        auto objectName = _<ObjectsIndex>().GetObjectName(object->GetType());
        auto quantity = object->GetQuantity();
        if (quantity == 1)
            m_objectHoverTextLines.push_back(objectName);
        else if (quantity > 1) {
            m_objectHoverTextLines.push_back(std::to_string(quantity) + "x " + objectName);
        }
    }
}

void ObjectHovering::Render(UserID userID) const {
    auto mousePos = _<EngineGet>().GetMousePosition(userID);
    
    auto lineX = mousePos.value().x + 0.015f;
    auto lineY = mousePos.value().y;
    
    for (auto line : m_objectHoverTextLines) {
        UserSendDrawText(userID, line, {lineX, lineY});
        lineY += 0.02f;
    }
}
}