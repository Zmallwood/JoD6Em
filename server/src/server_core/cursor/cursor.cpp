// cursor.cpp
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
//

#include "cursor.h"
#include "server_core/net/user_connection.h"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace jod {
    cursor::cursor(user_connection& user_connection)
        : m_user_connection(user_connection) {
    }
    
    void
    cursor::render(websocket::stream<tcp::socket>& ws){
        auto mousePos = m_user_connection.m_mousePosition; // Get current mouse position.
        // Obtain cursor dimensions.
        auto cursorWidth = k_cursorSize;
        auto cursorHeight = k_cursorSize*m_user_connection.get_aspect_ratio();
        // Calculate cursor position.
        auto cursorX = mousePos.x - cursorWidth / 2;
        auto cursorY = mousePos.y - cursorHeight / 2;
        // Create render destination rectangle.
        auto cursorDest = rectf{cursorX, cursorY, cursorWidth, cursorHeight};
        // Render the cursor image.
        m_user_connection.send_image_draw_instruction(ws, k_cursorImageName, cursorDest);
    }
}