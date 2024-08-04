/*
 * ImageRenderer.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ClientCore/Graphics/Rendering/RenderingCore/RendererBase.h"

namespace jod {
    /// @brief Allocates image resources and enabled rendering images to the browser.
    class ImageRenderer : public RendererBase {
    public:
        /// @brief Construct a new Image Renderer object by creating the GL shader program associates
        ///        with image rendering.
        ImageRenderer();
        
        /// @brief Destroy the Image Renderer object by cleaning up allocated resources associated
        ///        with image rendering.
        ~ImageRenderer();
        
        /// @brief Allocates resources for a new image and return the ID used to render with these
        ///        resources.
        /// @return rid Resource ID used to render an image with the allocated resources.
        rid NewImage();
        
        /// @brief Render an image to the browser.
        /// @param rid Resource ID previously allocated.
        /// @param image_name Name of image to render.
        /// @param destination Destination rectangle to render the image at.
        /// @param repeat_texture True if repeat image as pattern or false for fitting it to
        /// @param texture_fill_amount Used to modify pattern repetition amount.
        /// @param color Used to modify overall color of the image.
        void DrawImage(
            rid rid,
            std::string_view image_name,
            const rectf &destination,
            bool repeat_texture = false,
            sizef texture_fill_amount = {1.0f, 1.0f},
            colorf color = {1.0f, 1.0f, 1.0f});
        
        /// @brief Render an image to the browser.
        /// @param rid Resource ID previously allocated.
        /// @param image_name_hash Hash code of name of image to render.
        /// @param destination Destination rectangle to render the image at.
        /// @param repeat_texture True if repeat image as pattern or false for fitting it to destination rectangle.
        /// @param texture_fill_amount Used to modify pattern repetition amount.
        /// @param color Used to modify overall color of the image.
        void DrawImage(
            rid rid,
            int image_name_hash,
            const rectf &destination,
            bool repeat_texture = false,
            sizef texture_fill_amount = {1.0f, 1.0f},
            colorf color = {1.0f, 1.0f, 1.0f});
    };
}