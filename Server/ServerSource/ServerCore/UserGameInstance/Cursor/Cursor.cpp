/*
 * Cursor.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Cursor.hpp"
#include "ServerCore/Net/UserConnection.hpp"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace JoD {
    Cursor::Cursor(UserConnection& user_connection)
        : m_user_connection(user_connection) {
    }
    
    void
    Cursor::Render(WebSocket& ws){
        auto mouse_position = m_user_connection.m_mouse_position; // Get current mouse position.
        // Obtain cursor dimensions.
        auto cursor_width = k_cursor_size;
        auto cursor_height = k_cursor_size*m_user_connection.GetAspectRatio();
        // Calculate cursor position.
        auto cursor_x = mouse_position.x - cursor_width / 2;
        auto cursor_y = mouse_position.y - cursor_height / 2;
        // Create render destination rectangle.
        auto cursor_destination = RectF{
            cursor_x, cursor_y, cursor_width,
            cursor_height};
        // Render the cursor image.
        m_user_connection.SendImageDrawInstruction(
            ws, k_cursor_image_name,
            cursor_destination);
    }
}