// Copyright (c) 2024 Andreas Åkerberg.
#pragma once
namespace jod {
    class Client;
    class TileHovering {
    public:
        TileHovering(Client &client);
        void Update();
        
        Point m_hoveredCoordinate = {-1, -1};
    private:
        Client &m_client;
    };
    class MouseMovement {
    public:
        MouseMovement(Client &client);
        void Update();
    private:
        Client &m_client;
    };
}