// Copyright (c) 2024 Andreas Åkerberg.
#pragma once

namespace jod {
    class Client;
    
    class Cursor {
    public:
        Cursor(Client& client);
        void Render(boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& ws);
    private:
        Client& m_client;
        const std::string k_cursorImageName = "CursorDefault"; ///< Image name for default cursor style.
        const float k_cursorSize = 0.03f; ///< Size of rendered cursor symbol.
    };
}