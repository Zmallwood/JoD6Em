// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
    class ServerEngine;

    class Client
    {
      public:
        Client(boost::asio::ip::tcp::socket socket);
        void
        SendImageDrawInstruction(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws,
                                 std::string_view imageName, RectF dest);
        void SendPresentCanvasInstruction(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);

      private:
        void DoSession(boost::asio::ip::tcp::socket socket);

        std::shared_ptr<ServerEngine> m_serverEngine;
    };
}