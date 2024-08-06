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
#include "Font.hpp"

namespace JoD {
    
    TextRenderer::TextRenderer() {
        
        // Required to call before using SDL_ttf.
        TTF_Init();
        
        // Construct font path.
        auto fontPath = k_relFontsPath + "default_font.ttf";
        
        // Create font objects for all sizes.
        auto font10 = std::make_shared<Font>(fontPath, 10);
        auto font20 = std::make_shared<Font>(fontPath, 20);
        auto font30 = std::make_shared<Font>(fontPath, 30);
        auto font50 = std::make_shared<Font>(fontPath, 50);
        
        // Store the font objects by their sizes.
        m_fonts.insert({FontSizes::_10, font10});
        m_fonts.insert({FontSizes::_20, font20});
        m_fonts.insert({FontSizes::_30, font30});
        m_fonts.insert({FontSizes::_50, font50});
    }
    
    void TextRenderer::RenderText(
        RID rid, std::string_view text,
        ColorF color,
        bool centerAlign, FontSizes fontSize,
        std::string &out_uniqueNameID,
        SizeF &out_dimensions) const {
        
        // Get main font object.
        auto font = m_fonts.at(fontSize)->m_font;
        
        // Check that its been created correctly.
        if (!font) {
            
            return;
        }
        
        // Create SDL-type colors.
        auto colorSDL = ToSDLColor(color);
        auto outlineColorSDL = ToSDLColor(k_outlineColor);
        
        // Render text outline onto surface.
        auto textOutlineSurface =
            TTF_RenderText_Blended(
                m_fonts.at(fontSize)->m_outlineFont.get(),
                text.data(), outlineColorSDL);
        
        // Check that the surface was created correctly.
        if (!textOutlineSurface) {
            
            return;
        }
        
        // Render main text onto surface.
        auto textSurface = TTF_RenderText_Blended(
            font.get(), text.data(),
            colorSDL);
        
        // Check that the surface was created correctly.
        if (!textSurface) {
            
            return;
        }
        
        // Start using 2D textures.
        glEnable(GL_TEXTURE_2D);
        
        // Get image name for previously created blank image.
        auto uniqueNameID = m_uniqueNameIDs.at(rid);
        
        // Get image ID for the preallocated blank image.
        auto imageID = _<ImageBank>().GetImage(uniqueNameID);
        
        // Bind this image.
        glBindTexture(GL_TEXTURE_2D, imageID);
        
        // Set necessary texture parameters.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        // Get dimensions of rendered outline surface.
        auto width = textOutlineSurface->w;
        auto height = textOutlineSurface->h;
        
        // Create empty RGB surface.
        auto image = SDL_CreateRGBSurface(
            SDL_SWSURFACE, width, height, 32, 0x000000FF,
            0x0000FF00, 0x00FF0000, 0xFF000000);
        
        auto canvasSize = GetCanvasSize();
        
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
        textDestBox.x += Font::k_fontOutlineWidth;
        textDestBox.w -= 2 * Font::k_fontOutlineWidth;
        textDestBox.y += Font::k_fontOutlineWidth;
        textDestBox.h -= 2 * Font::k_fontOutlineWidth;
        
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
        auto outWidth =
            textSurface ? static_cast<float>(textSurface->w) /
            canvasSize.w : 0;
        
        // Get final rendered height.
        auto outHeight =
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
        auto id = s_idCounter++;
        
        // Produce an unique image name based on the ID.
        auto uniqueName = "RenderedImage" + std::to_string(id);
        
        // Create a blank image with the above name.
        auto ridImage = _<ImageBank>().CreateBlankImage(uniqueName);
        
        // Store the images ID and unique name.
        m_uniqueNameIDs.insert({ridImage, uniqueName});
        
        // Allocate image resources from the ImageRenderer.
        auto ridGLResource = _<ImageRenderer>().NewImage();
        
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
        
        std::string uniqueNameID;
        SizeF size;
        
        RenderText(
            rid, text, color, centerAlign, fontSize, uniqueNameID,
            size);
        
        auto canvasSize = GetCanvasSize();
        
        auto rectangle = BoxF{position.x, position.y, size.w, size.h};
        
        int textWidth;
        int textHeight;
        
        TTF_SizeText(
            m_fonts.at(fontSize)->m_font.get(), text.data(), &textWidth,
            &textHeight);
        
        if (centerAlign) {
            
            rectangle.x -= static_cast<float>(textWidth) /
                           static_cast<float>(canvasSize.h) /
                           2.0f / GetAspectRatio();
            
            rectangle.y -=
                static_cast<float>(textHeight) /
                static_cast<float>(canvasSize.h) /
                2.0f;
        }
        
        auto scale = 1.0f;
        
        rectangle.x += rectangle.w / 2.0f - rectangle.w / 2.0f * scale;
        rectangle.y += rectangle.h / 2.0f - rectangle.h / 2.0f * scale;
        rectangle.w *= scale;
        rectangle.h *= scale;
        
        auto ridGLResource = m_ridsGLResources.at(rid);
        
        _<ImageRenderer>().DrawImage(
            ridGLResource, uniqueNameID, rectangle,
            false);
    }
    
    SizeF TextRenderer::MeasureString(
        std::string_view text,
        FontSizes font_size) const {
        
        auto font = m_fonts.at(font_size)->m_font;
        
        int textWidth;
        int textHeight;
        
        TTF_SizeText(font.get(), text.data(), &textWidth, &textHeight);
        
        auto canvasSize = GetCanvasSize();
        
        return {static_cast<float>(textWidth) / canvasSize.w,
                static_cast<float>(textHeight) / canvasSize.h};
    }
}