// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
  class ServerEngine;

  class Client
  {
   public:
    Client(boost::asio::ip::tcp::socket socket);
    void SendImageDrawInstruction(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws,
                                  std::string_view imageName, RectF dest);
    void SendImageDrawInstruction(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws,
                                  int imageNameHash, RectF dest);
    void
    SendPresentCanvasInstruction(boost::beast::websocket::stream<boost::asio::ip::tcp::socket> &ws);

    float GetAspectRatio();

   private:
    void DoSession(boost::asio::ip::tcp::socket socket);

    std::shared_ptr<ServerEngine> m_serverEngine;
    Size m_canvasSize;
  };
}