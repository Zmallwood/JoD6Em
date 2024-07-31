// Copyright (c) 2024 Andreas Åkerberg.
#pragma once
namespace jod {
    class ServerEngine;
    class Player;
    class TileHovering;
    class MouseMovement;
    class Cursor;
    class Client {
    public:
        Client(boost::asio::ip::tcp::socket socket);
        void
        SendImageDrawInstruction(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws,
                                 std::string_view imageName, RectF dest);
        void
        SendImageDrawInstruction(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws,
                                 int imageNameHash, RectF dest);
        void SendPresentCanvasInstruction(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);
        float GetAspectRatio();
        
        std::shared_ptr<Player> m_player;
        std::shared_ptr<TileHovering> m_tileHovering;
        std::shared_ptr<MouseMovement> m_mouseMovement;
        PointF m_mousePosition;
        std::shared_ptr<ServerEngine> m_serverEngine;
        std::shared_ptr<Cursor> m_cursor;
    private:
        void DoSession(boost::asio::ip::tcp::socket socket);
        
        Size m_canvasSize;
    };
}