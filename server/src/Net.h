// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
  namespace MessageCodes
  {
    constexpr int k_drawImageInstr = 1;
    constexpr int k_applyBuffer = 2;
    constexpr int k_tick = 3;
    constexpr int k_mouseDown = 4;
    constexpr int k_canvasSize = 5;
  }

  class Client;

  class WebSocketServer
  {
   public:
    void Start(std::string socketAddress, std::string socketPort);

   private:
    std::vector<std::shared_ptr<Client>> m_clients;
  };
}