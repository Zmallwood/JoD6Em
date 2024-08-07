/*
 * GUI.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "GUIComponent.hpp"

namespace JoD {
    class GUI {
      public:
        void Update();
        
        void Render(WebSocket &webSocket) const;
        
        std::vector<std::unique_ptr<GUIComponent>> m_components;
    };
}