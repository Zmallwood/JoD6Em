/*
 * GUI.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    class GUI {
      public:
        void Update();
        
        void Render(WebSocket &webSocket) const;
    };
}