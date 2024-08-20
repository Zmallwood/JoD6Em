/*
 * ImageRenderer.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "ClientCore/Graphics/Rendering/RenderingCore/RendererBase.hpp"

namespace JoD {
/// Allocates image resources and enabled rendering images to the browser.
class ImageRenderer : public RendererBase {
  public:
/// Construct a new Image Renderer object by creating the GL shader program associates
/// with image rendering.
    ImageRenderer();
    
/// Destroy the Image Renderer object by cleaning up allocated resources associated
/// with image rendering.
    ~ImageRenderer();
    
/// Allocates resources for a new image and return the ID used to render with these
/// resources.
///
/// @return rid Resource ID used to render an image with the allocated resources.
    RID NewImage();

/// Render an image to the browser.
/// @param rid Resource ID previously allocated.
/// @param imageName Name of image to render.
/// @param destination Destination rectangle to render the image at.
/// @param repeatTexture True if repeat image as pattern or false for fitting it to
/// @param textureFillAmount Used to modify pattern repetition amount.
/// @param color Used to modify overall color of the image.
    void DrawImage(
        RID rid,
        std::string_view imageName,
        const BoxF &destination,
        bool repeatTexture = false,
        SizeF textureFillAmount = {1.0f, 1.0f},
        ColorF color = Colors::white) const;
    
/// Render an image to the browser.
/// @param rid Resource ID previously allocated.
/// @param imageNameHash Hash code of name of image to render.
/// @param destination Destination rectangle to render the image at.
/// @param repeatTexture True if repeat image as pattern or false for fitting it to destination rectangle.
/// @param textureFillAmount Used to modify pattern repetition amount.
/// @param color Used to modify overall color of the image.
    void DrawImage(
        RID rid,
        int imageNameHash,
        const BoxF &destination,
        bool repeatTexture = false,
        SizeF textureFillAmount = {1.0f, 1.0f},
        ColorF color = Colors::white) const;
};
}
