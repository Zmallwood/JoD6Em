/*
 * Cursor.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Cursor.h"
#include "ServerCore/Net/UserConnection.h"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace jod {
    cursor::cursor(user_connection& user_connection)
        : m_user_connection(user_connection) {
    }
    
    void
    cursor::render(websocket::stream<tcp::socket>& ws){
        auto mouse_position = m_user_connection.m_mouse_position; // Get current mouse position.
        // Obtain cursor dimensions.
        auto cursor_width = k_cursor_size;
        auto cursor_height = k_cursor_size*m_user_connection.get_aspect_ratio();
        // Calculate cursor position.
        auto cursor_x = mouse_position.x - cursor_width / 2;
        auto cursor_y = mouse_position.y - cursor_height / 2;
        // Create render destination rectangle.
        auto cursor_destination = rectf{
            cursor_x, cursor_y, cursor_width,
            cursor_height};
        // Render the cursor image.
        m_user_connection.send_image_draw_instruction(
            ws, k_cursor_image_name,
            cursor_destination);
    }
}