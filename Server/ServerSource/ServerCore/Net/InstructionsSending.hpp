/*
 * InstructionsSending.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Send an image drawing instruction to the user.
    ///
    /// @param webSocket Socket object.
    /// @param imageName Name of image to draw.
    /// @param destination Destination to draw the image at.
    ///
    void SendImageDrawInstruction(
        WebSocket &webSocket,
        std::string_view imageName,
        BoxF destination);
    
    ///
    /// Send an image drawing instruction to the user.
    ///
    /// @param webSocket Socket object.
    /// @param imageNamehash Hash code of image name to draw.
    /// @param destination Destination to draw the image at.
    ///
    void SendImageDrawInstruction(
        WebSocket &webSocket,
        int imageNamehash,
        BoxF destination);
    
    ///
    /// Send a text drawing instruction to the user.
    ///
    /// @param webSocket Socket object.
    /// @param text Text to draw.
    /// @param position Position to draw the text at.
    /// @param centerAlign
    ///
    void SendTextDrawInstruction(
        WebSocket &webSocket,
        std::string_view text, PointF position, bool centerAlign = false);
    
    ///
    /// Send instruction to present canvas to the user.
    ///
    /// @param webSocket Socket object.
    ///
    void SendPresentCanvasInstruction(WebSocket &webSocket);
    
    ///
    /// Send request to user to retrieve dimensions for an image.
    ///
    /// @param webSocket Socket object.
    /// @param imageNameHash Hash code of image name to get dimensions for.
    ///
    void SendRequestImageDimensions(
        WebSocket &webSocket,
        int imageNameHash);
}