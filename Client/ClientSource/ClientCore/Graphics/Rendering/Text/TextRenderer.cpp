/*
 * TextRenderer.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "TextRenderer.hpp"
#include "ClientCore/Assets/ImageBank.hpp"
#include "ClientCore/Graphics/Rendering/Images/ImageRenderer.hpp"
#include "ClientCore/Graphics/Rendering/Text/FontSizes.hpp"
#include "Common/CanvasUtilities.hpp"

namespace JoD {
    
    TextRenderer::TextRenderer() {
        
        // Required to call before using SDL_ttf.
        TTF_Init();
        
        // Construct font path.
        const auto fontPath = k_relFontsPath + "default_font.ttf";
        
        // Create font objects for all sizes.
        auto font10 = std::make_unique<const Font>(fontPath, 10);
        auto font20 = std::make_unique<const Font>(fontPath, 20);
        auto font30 = std::make_unique<const Font>(fontPath, 30);
        auto font50 = std::make_unique<const Font>(fontPath, 50);
        
        // Store the font objects by their sizes.
        m_fonts.insert({FontSizes::_10, std::move(font10)});
        m_fonts.insert({FontSizes::_20, std::move(font20)});
        m_fonts.insert({FontSizes::_30, std::move(font30)});
        m_fonts.insert({FontSizes::_50, std::move(font50)});
    }
    
    void TextRenderer::RenderText(
        RID rid, std::string_view text,
        ColorF color,
        bool centerAlign, FontSizes fontSize,
        std::string &out_uniqueNameID,
        SizeF &out_dimensions) const {
        
        // Get main font object.
        const auto &font = m_fonts.at(fontSize)->GetFont();
        
        // Check that its been created correctly.
        if (!font) {
            
            return;
        }
        
        // Create SDL-type colors.
        const auto colorSDL = ToSDLColor(color);
        const auto outlineColorSDL = ToSDLColor(k_outlineColor);
        
        // Render text outline onto surface.
        const auto textOutlineSurface =
            TTF_RenderText_Blended(
                m_fonts.at(fontSize)->GetOutlineFont().get(),
                text.data(), outlineColorSDL);
        
        // Check that the surface was created correctly.
        if (!textOutlineSurface) {
            
            return;
        }
        
        // Render main text onto surface.
        const auto textSurface = TTF_RenderText_Blended(
            font.get(), text.data(),
            colorSDL);
        
        // Check that the surface was created correctly.
        if (!textSurface) {
            
            return;
        }
        
        // Start using 2D textures.
        glEnable(GL_TEXTURE_2D);
        
        // Get image name for previously created blank image.
        const auto uniqueNameID = m_uniqueNameIDs.at(rid);
        
        // Get image ID for the preallocated blank image.
        const auto imageID = _<ImageBank>().GetImage(uniqueNameID);
        
        // Bind this image.
        glBindTexture(GL_TEXTURE_2D, imageID);
        
        // Set necessary texture parameters.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        // Get dimensions of rendered outline surface.
        const auto width = textOutlineSurface->w;
        const auto height = textOutlineSurface->h;
        
        // Create empty RGB surface.
        auto image = SDL_CreateRGBSurface(
            SDL_SWSURFACE, width, height, 32, 0x000000FF,
            0x0000FF00, 0x00FF0000, 0xFF000000);
        
        const auto canvasSize = GetCanvasSize();
        
        // Create boxes for source and destination
        // for main and outline renderings.
        SDL_Rect textSourceBox;
        SDL_Rect textOutlineSourceBox;
        SDL_Rect textDestBox;
        SDL_Rect textOutlineDestBox;
        
        // Source bounds for main font rendering.
        textSourceBox =
            SDL_Rect{0, 0, textSurface ? textSurface->w : 0,
                     textSurface ? textSurface->h : 0};
        
        // Source bounds for outline font rendering.
        textOutlineSourceBox =
            SDL_Rect{0, 0, textOutlineSurface ? textOutlineSurface->w : 0,
                     textOutlineSurface ? textOutlineSurface->h : 0};
        
        // Destination bounds for main font rendering.
        textDestBox = textSourceBox;
        textDestBox.x += Font::GetFontOutlineWidth();
        textDestBox.w -= 2 * Font::GetFontOutlineWidth();
        textDestBox.y += Font::GetFontOutlineWidth();
        textDestBox.h -= 2 * Font::GetFontOutlineWidth();
        
        // Destination bounds for outline font rendering.
        textOutlineDestBox = textOutlineSourceBox;
        textOutlineDestBox.y = 1;
        
        // Blit outline font rendering onto final image surface.
        SDL_BlitSurface(
            textOutlineSurface, &textOutlineSourceBox, image,
            &textOutlineDestBox);
        
        // Blit main font rendering onto final image surface.
        SDL_BlitSurface(
            textSurface, &textSourceBox, image,
            &textDestBox);
        
        // Transform SDL surface pixels into GL texture.
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, image->pixels);
        
        // Get final rendered with.
        const auto outWidth =
            textSurface ? static_cast<float>(textSurface->w) /
            canvasSize.w : 0;
        
        // Get final rendered height.
        const auto outHeight =
            textSurface ? static_cast<float>(textSurface->h) /
            canvasSize.h : 0;
        
        // Send the unique name ID to out-parameter.
        out_uniqueNameID = uniqueNameID;
        
        // Send the dimensions to out parameter.
        out_dimensions = {outWidth, outHeight};
        
        // Free surfaces not needed anymore.
        SDL_FreeSurface(image);
        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(textOutlineSurface);
    }
    
    RID TextRenderer::NewString() {
        
        // Number of strings been preallocated.
        static int s_idCounter = 0;
        
        // Set this new strings ID.
        const auto id = s_idCounter++;
        
        // Produce an unique image name based on the ID.
        const auto uniqueName = "RenderedImage" + std::to_string(id);
        
        // Create a blank image with the above name.
        const auto ridImage = _<ImageBank>().CreateBlankImage(uniqueName);
        
        // Store the images ID and unique name.
        m_uniqueNameIDs.insert({ridImage, uniqueName});
        
        // Allocate image resources from the ImageRenderer.
        const auto ridGLResource = _<ImageRenderer>().NewImage();
        
        // Store also the ImageRenderer resource ID.
        m_ridsGLResources.insert({ridImage, ridGLResource});
        
        // Return the RID for the newly created blank image.
        return ridImage;
    }
    
    void TextRenderer::DrawString(
        RID rid, std::string_view text,
        PointF position, ColorF color,
        bool centerAlign,
        FontSizes fontSize) const {
        
        // Undefined variables will be set in the RenderText function call.
        std::string uniqueNameID;
        SizeF size;
        
        // Execute the actual text rendering operations.
        RenderText(
            rid, text, color, centerAlign, fontSize, uniqueNameID,
            size);
        
        const auto canvasSize = GetCanvasSize();
        
        // Create final render destination box.
        auto box = BoxF{position.x, position.y, size.w, size.h};
        
        // Undefined variables, will get values from TTF_SizeText.
        int textWidth;
        int textHeight;
        
        // Measure the rendered text.
        TTF_SizeText(
            m_fonts.at(fontSize)->GetFont().get(), text.data(), &textWidth,
            &textHeight);
        
        // If the text should be aligned at its center.
        if (centerAlign) {
            
            // Move the text x coordinate accordingly.
            box.x -=
                static_cast<float>(textWidth) /
                static_cast<float>(canvasSize.h) /
                2.0f / GetAspectRatio();
            
            // Move the text y coordinate accordingly.
            box.y -=
                static_cast<float>(textHeight) /
                static_cast<float>(canvasSize.h) /
                2.0f;
        }
        
        // Ability to scale the text before rendering.
        const auto scale = 1.0f;
        
        box.x += box.w / 2.0f - box.w / 2.0f * scale;
        box.y += box.h / 2.0f - box.h / 2.0f * scale;
        box.w *= scale;
        box.h *= scale;
        
        // Get the RID associated with the image onto which the
        // text has been rendered.
        const auto ridGLResource = m_ridsGLResources.at(rid);
        
        // Do the actual rendering operation.
        _<ImageRenderer>().DrawImage(
            ridGLResource, uniqueNameID, box,
            false);
    }
    
    SizeF TextRenderer::MeasureString(
        std::string_view text,
        FontSizes font_size) const {
        
        // Get the main font object.
        const auto &font = m_fonts.at(font_size)->GetFont();
        
        // To be filled with rendered text dimensions.
        int textWidth;
        int textHeight;
        
        // Get the dimensions.
        TTF_SizeText(font.get(), text.data(), &textWidth, &textHeight);
        
        const auto canvasSize = GetCanvasSize();
        
        // Return the normalized dimensions.
        return {static_cast<float>(textWidth) / canvasSize.w,
                static_cast<float>(textHeight) / canvasSize.h};
    }
}