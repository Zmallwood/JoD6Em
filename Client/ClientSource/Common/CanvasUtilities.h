/*
 * CanvasUtilities.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    /// @brief Get the size of canvas in the web browser.
    /// @return size Canvas size in pixels.
    Size GetCanvasSize();
    
    /// @brief Get the aspect ratio of the canvas in the web browser.
    /// @return float The aspect ratio (width/height).
    float GetAspectRatio();
    
    /// @brief Converts a width to corresponding height with regards to aspect ratio.
    /// @param width The width value to convert.
    /// @return float The corresponding height.
    float ConvertWidthToHeight(float width);

    /// @brief Converts a height to corresponding width with regards to aspect ratio.
    /// @param width The height value to convert.
    /// @return float The corresponding width.
    float ConvertHeightToWidth(float height);
    
    /// @brief Converts a height to corresponding width with regards to aspect ratio.
    /// @param height The height value to convert.
    /// @return float The corresponding width.
    
    SDL_Color ToSDLColor(ColorF color);
}