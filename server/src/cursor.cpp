// Copyright (c) 2024 Andreas Åkerberg.
#include "cursor.h"
#include "client.h"

namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace jod {
    Cursor::Cursor(Client& client)
        : m_client(client) {
    }
    void
    Cursor::Render(websocket::stream<tcp::socket>& ws){
        auto mousePos = m_client.m_mousePosition; // Get current mouse position.
        // Obtain cursor dimensions.
        auto cursorWidth = k_cursorSize;
        auto cursorHeight = k_cursorSize*m_client.GetAspectRatio();
        // Calculate cursor position.
        auto cursorX = mousePos.x - cursorWidth / 2;
        auto cursorY = mousePos.y - cursorHeight / 2;
        // Create render destination rectangle.
        auto cursorDest = RectF{cursorX, cursorY, cursorWidth, cursorHeight};
        // Render the cursor image.
        m_client.SendImageDrawInstruction(ws, k_cursorImageName, cursorDest);
    }
}