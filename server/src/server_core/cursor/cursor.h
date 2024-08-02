// cursor.h
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
//

#pragma once

namespace jod {
    class user_connection;
    
    class cursor {
    public:
        cursor(user_connection& user_connection);
        
        void render(
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& ws);
        
    private:
        user_connection& m_user_connection;
        
        const std::string k_cursorImageName = "CursorDefault"; ///< Image name for default cursor style.

        const float k_cursorSize = 0.03f; ///< Size of rendered cursor symbol.
    };
}