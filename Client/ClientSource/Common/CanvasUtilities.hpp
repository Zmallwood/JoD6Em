/*
 * CanvasUtilities.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
/// Get the size of canvas in the web browser.
/// @return size Canvas size in pixels.
Size GetCanvasSize();

/// Get the aspect ratio of the canvas in the web browser.
/// @return float The aspect ratio (width/height).
float GetAspectRatio();

/// Converts a width to corresponding height with regards to aspect ratio.
/// @param width The width value to convert.
/// @return float The corresponding height.
float ConvertWidthToHeight(float width);

/// Converts a height to corresponding width with regards to aspect ratio.
/// @param width The height value to convert.
/// @return float The corresponding width.
float ConvertHeightToWidth(float height);

///  Converts a ColorF object to corresponding SDL_Color type.
/// @param color Color to be converted.
/// @return SDL_Color Resulting SDL_Color object.
SDL_Color ToSDLColor(ColorF color);
}