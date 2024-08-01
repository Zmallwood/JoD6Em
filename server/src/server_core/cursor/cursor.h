// cursor.h
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
///////////////////////////////////////////////////////////

#pragma once

namespace jod {
    class client;
    
    class cursor {
    public:
        cursor(client& client);
        
        void render(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& ws);
        
    private:
        client& m_client;
        
        const std::string k_cursorImageName = "CursorDefault"; ///< Image name for default cursor style.

        const float k_cursorSize = 0.03f; ///< Size of rendered cursor symbol.
    };
}