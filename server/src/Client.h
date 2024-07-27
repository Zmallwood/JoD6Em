// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
    class Client
    {
      public:
        Client(boost::asio::ip::tcp::socket socket);

      private:
        void DoSession(boost::asio::ip::tcp::socket socket);
        void SendImageDrawInstruction(boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& ws, std::string_view imageName, RectF dest);
        void SendPresentCanvasInstruction(boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& ws);
    };
}