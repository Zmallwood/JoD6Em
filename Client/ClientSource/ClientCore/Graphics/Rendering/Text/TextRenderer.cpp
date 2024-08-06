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
        
        TTF_Init();
        
        auto fontPath = k_relFontsPath + "default_font.ttf";
        
        auto font10 = std::make_shared<Font>(fontPath, 10);
        auto font20 = std::make_shared<Font>(fontPath, 20);
        auto font30 = std::make_shared<Font>(fontPath, 30);
        auto font50 = std::make_shared<Font>(fontPath, 50);
        
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
        
        auto font = m_fonts.at(fontSize)->m_font;
        
        if (!font) {
            
            return;
        }
        
        auto colorSDL = ToSDLColor(color);
        auto outlineColorSDL = ToSDLColor(k_outlineColor);
        
        auto textOutlineSurface =
            TTF_RenderText_Blended(
                m_fonts.at(fontSize)->m_outlineFont.get(),
                text.data(), outlineColorSDL);
        
        if (!textOutlineSurface) {
            
            return;
        }
        
        auto textSurface = TTF_RenderText_Blended(
            font.get(), text.data(),
            colorSDL);
        
        if (!textSurface) {
            
            return;
        }
        
        glEnable(GL_TEXTURE_2D);
        
        auto uniqueNameID = m_uniqueNameIDs.at(rid);
        
        auto imageID = _<ImageBank>().GetImage(uniqueNameID);
        
        glBindTexture(GL_TEXTURE_2D, imageID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        auto width = textOutlineSurface->w;
        auto height = textOutlineSurface->h;
        
        auto image = SDL_CreateRGBSurface(
            SDL_SWSURFACE, width, height, 32, 0x000000FF,
            0x0000FF00, 0x00FF0000, 0xFF000000);
        
        auto canvasSize = GetCanvasSize();
        
        SDL_Rect textSourceRectangle;
        SDL_Rect textOutlineSourceRectangle;
        SDL_Rect textDestinationRectangle;
        SDL_Rect textOutlineDestinationRectangle;
        
        textSourceRectangle =
            SDL_Rect{0, 0, textSurface ? textSurface->w : 0,
                     textSurface ? textSurface->h : 0};
        
        textOutlineSourceRectangle =
            SDL_Rect{0, 0, textOutlineSurface ? textOutlineSurface->w : 0,
                     textOutlineSurface ? textOutlineSurface->h : 0};
        
        textDestinationRectangle = textSourceRectangle;
        
        textDestinationRectangle.x += Font::k_fontOutlineWidth;
        textDestinationRectangle.w -= 2 * Font::k_fontOutlineWidth;
        textDestinationRectangle.y += Font::k_fontOutlineWidth;
        textDestinationRectangle.h -= 2 * Font::k_fontOutlineWidth;
        
        textOutlineDestinationRectangle = textOutlineSourceRectangle;
        textOutlineDestinationRectangle.y = 1;
        
        
        SDL_BlitSurface(
            textOutlineSurface, &textOutlineSourceRectangle, image,
            &textOutlineDestinationRectangle);
        
        SDL_BlitSurface(
            textSurface, &textSourceRectangle, image,
            &textDestinationRectangle);
        
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, image->pixels);
        
        auto outWidth = textSurface ? static_cast<float>(textSurface->w) /
                        canvasSize.w : 0;
        
        auto outHeight = textSurface ? static_cast<float>(textSurface->h) /
                         canvasSize.h : 0;
        
        out_uniqueNameID = uniqueNameID;
        out_dimensions = {outWidth, outHeight};
        
        SDL_FreeSurface(image);
        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(textOutlineSurface);
    }
    
    RID TextRenderer::NewString() {
        
        static int s_idCounter = 0;
        
        auto id = s_idCounter++;
        
        auto uniqueName = "RenderedImage" + std::to_string(id);
        
        auto ridImage = _<ImageBank>().CreateBlankImage(uniqueName);
        
        m_uniqueNameIDs.insert({ridImage, uniqueName});
        
        auto ridGLResource = _<ImageRenderer>().NewImage();
        
        m_ridsGLResources.insert({ridImage, ridGLResource});
        
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