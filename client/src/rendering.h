// Copyright (c) 2024 Andreas Åkerberg.
#pragma once
#include "rendering_core.h"
namespace jod {
    /////////////////////////////////////////////////
    /// \brief Allocates image resources and enabled rendering images to the browser.
    /////////////////////////////////////////////////
    class image_renderer : public renderer_base {
    public:
        /////////////////////////////////////////////////
        /// \brief Construct a new Image Renderer object by creating the GL shader program associates
        ///        with image rendering.
        /////////////////////////////////////////////////
        image_renderer();
        /////////////////////////////////////////////////
        /// \brief Destroy the Image Renderer object by cleaning up allocated resources associated
        ///        with image rendering.
        /////////////////////////////////////////////////
        ~image_renderer();
        /////////////////////////////////////////////////
        /// \brief Allocates resources for a new image and return the ID used to render with these
        ///        resources.
        /// \return RID Resource ID used to render an image with the allocated resources.
        /////////////////////////////////////////////////
        RID new_image();
        /////////////////////////////////////////////////
        /// \brief Render an image to the browser.
        /// \param rid Resource ID previously allocated.
        /// \param imageName Name of image to render.
        /// \param dest Destination rectangle to render the image at.
        /// \param repeatTexture True if repeat image as pattern or false for fitting it to
        /// \param textureFillAmount Used to modify pattern repetition amount.
        /// \param color Used to modify overall color of the image.
        /////////////////////////////////////////////////
        void draw_image(RID rid, std::string_view imageName, const RectF &dest,
                       bool repeatTexture = false, SizeF textureFillAmount = {1.0f, 1.0f},
                       ColorF color = {1.0f, 1.0f, 1.0f});
        /////////////////////////////////////////////////
        /// \brief Render an image to the browser.
        /// \param rid Resource ID previously allocated.
        /// \param imageNameHash Hash code of name of image to render.
        /// \param dest Destination rectangle to render the image at.
        /// \param repeatTexture True if repeat image as pattern or false for fitting it to destination rectangle.
        /// \param textureFillAmount Used to modify pattern repetition amount.
        /// \param color Used to modify overall color of the image.
        /////////////////////////////////////////////////
        void draw_image(RID rid, int imageNameHash, const RectF &dest, bool repeatTexture = false,
                       SizeF textureFillAmount = {1.0f, 1.0f}, ColorF color = {1.0f, 1.0f, 1.0f});
    };
}