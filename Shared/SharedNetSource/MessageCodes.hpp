/*
 * MessageCodes.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Available type of messages that can be sent over web sockets.
///
namespace MessageCodes {

constexpr int k_drawImageInstruction {1};   ///< Tells client to draw an image.
constexpr int k_applyBuffer {2};            ///< Tells client the instruction buffer is ready to be applied.
constexpr int k_leftMouseDown {3};          ///< Tells server left mouse button have been pressed.
constexpr int k_canvasSize {4};             ///< Sending a packet from client to server with canvas size.
constexpr int k_mousePosition {5};          ///< Sending a packed from client to server with mouse position.
constexpr int k_drawStringInstruction {6};  ///< Tells client to draw a string of text.
constexpr int k_rightMouseDown {7};         ///< Tells server right mouse button has been pressed.
constexpr int k_requestImageDimensions {8}; ///< Server request image dimensions from client.
constexpr int k_provideImageDimensions {9}; ///< Client provides requested image dimensions to server.
constexpr int k_leftMouseUp {10};
constexpr int k_rightMouseUp {11};
constexpr int k_drawImageRepeatInstruction {12};

}
}