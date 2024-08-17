/*
 * Canvas.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Canvas.hpp"
#include "Window.hpp"
#include "World.hpp"
#include "WorldArea.hpp"
#include "Tile.hpp"

namespace JoD {

void Canvas::mousePressEvent(QMouseEvent* event) {
    
    auto currTool = _<Window>().GetCurrTool();
    
    auto tileX = event->pos().x()/60;
    auto tileY = event->pos().y()/60;
    
    
    auto wArea = _<World>().GetCurrWorldArea();
    
    auto tile = wArea->GetTile(tileX, tileY);
    
    switch (currTool) {
        
        case Tools::SetGround:
            tile->SetGround(_<Window>().GetSelectedImageHash());
        break;
        
        case Tools::AddObject:
        
        break;
        
        case Tools::None:
        break;
    }
    
    _<Window>().repaint();
}

}