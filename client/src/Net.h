// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

#include "MessageCodes.h"

namespace jod
{
    /**
     * @brief Connects to to web socket server and enables sending messages over the connection
     * after it has opened.
     *
     */
    class WebSocketServerConnection
    {
      public:
        /**
         * @brief Open the connection to the web socket server.
         *
         */
        void Connect();

        /**
         * @brief Send message to the server.
         *
         * @param messageType Message type to be sent.
         */
        void SendMessage(int messageType);

        /**
         * @brief Web socket event object related to the opened connection.
         *
         */
        std::shared_ptr<const EmscriptenWebSocketOpenEvent> m_webSocketEvent;

      private:
        /**
         * @brief Host name of the server to connect to.
         *
         */
        const std::string k_host = "localhost";

        /**
         * @brief Port number to open the connection at.
         *
         */
        const int k_port = 8765;
    };
}