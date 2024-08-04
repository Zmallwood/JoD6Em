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
        auto font_path = k_rel_fonts_path + "default_font.ttf";
        auto font_20 = std::make_shared<Font>(font_path, 20);
        auto font_30 = std::make_shared<Font>(font_path, 30);
        auto font_50 = std::make_shared<Font>(font_path, 50);
        m_fonts.insert({FontSizes::_20, font_20});
        m_fonts.insert({FontSizes::_30, font_30});
        m_fonts.insert({FontSizes::_50, font_50});
        
    }
    
    void TextRenderer::RenderText(RID rid, std::string_view text,
                                    ColorF color,
                                    bool center_align, FontSizes font_size,
                                    std::string &out_unique_name_id,
                                    SizeF &out_size) const {
        auto font = m_fonts.at(font_size)->m_font;
        
        if (!font) return;
        
        auto color_sdl = ToSDLColor(color);
        auto outline_color_sdl = ToSDLColor(k_outline_color);
        auto text_outline_surface =
            TTF_RenderText_Blended(
                m_fonts.at(font_size)->m_outline_font.get(),
                text.data(), outline_color_sdl);
        
        if (!text_outline_surface)
            return;
        auto text_surface = TTF_RenderText_Blended(
            font.get(), text.data(),
            color_sdl);
        if (!text_surface)
            return;
        
        glEnable(GL_TEXTURE_2D);
        auto unique_name_id = m_unqiue_name_ids.at(rid);
        auto image_id = _<ImageBank>().GetImage(unique_name_id);
        
        glBindTexture(GL_TEXTURE_2D, image_id);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        auto width = text_outline_surface->w;
        auto height = text_outline_surface->h;
        
        auto image = SDL_CreateRGBSurface(
            SDL_SWSURFACE, width, height, 32, 0x000000FF,
            0x0000FF00, 0x00FF0000, 0xFF000000);
        auto canvas_size = GetCanvasSize();
        
        SDL_Rect text_source_rectangle;
        SDL_Rect text_outline_source_rectangle;
        SDL_Rect text_destination_rectangle;
        SDL_Rect text_outline_destination_rectangle;
        
        text_source_rectangle =
            SDL_Rect{0, 0, text_surface ? text_surface->w : 0,
                     text_surface ? text_surface->h : 0};
        text_outline_source_rectangle =
            SDL_Rect{0, 0, text_outline_surface ? text_outline_surface->w : 0,
                     text_outline_surface ? text_outline_surface->h : 0};
        text_destination_rectangle = text_source_rectangle;
        
        text_destination_rectangle.x += Font::k_font_outline_width;
        text_destination_rectangle.w -= 2 * Font::k_font_outline_width;
        text_destination_rectangle.y += Font::k_font_outline_width;
        text_destination_rectangle.h -= 2 * Font::k_font_outline_width;
        text_outline_destination_rectangle = text_outline_source_rectangle;
        text_outline_destination_rectangle.y = 1;
        
        
        SDL_BlitSurface(
            text_outline_surface, &text_outline_source_rectangle, image,
            &text_outline_destination_rectangle);
        SDL_BlitSurface(
            text_surface, &text_source_rectangle, image,
            &text_destination_rectangle);
        
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, image->pixels);
        auto out_width = text_surface ? static_cast<float>(text_surface->w) /
                         canvas_size.w : 0;
        auto out_height = text_surface ? static_cast<float>(text_surface->h) /
                          canvas_size.h : 0;
        out_unique_name_id = unique_name_id;
        out_size = {out_width, out_height};
        
        SDL_FreeSurface(image);
        SDL_FreeSurface(text_surface);
        SDL_FreeSurface(text_outline_surface);
    }
    
    RID TextRenderer::NewString() {
        static int s_id_counter = 0;
        auto id = s_id_counter++;
        auto unique_name = "RenderedImage" + std::to_string(id);
        auto rid_image = _<ImageBank>().CreateBlankImage(unique_name);
        m_unqiue_name_ids.insert({rid_image, unique_name});
        auto rid_gl_resource = _<ImageRenderer>().NewImage();
        m_rids_gl_resources.insert({rid_image, rid_gl_resource});
        return rid_image;
    }
    
    void TextRenderer::DrawString(RID rid, std::string_view text,
                                    PointF position, ColorF color,
                                    bool center_align,
                                    FontSizes font_size){
        std::string unique_name_id;
        SizeF size;
        
        RenderText(
            rid, text, color, center_align, font_size, unique_name_id,
            size);
        
        auto canvas_size = GetCanvasSize();
        auto rectangle = RectF{position.x, position.y, size.w, size.h};
        int text_w;
        int text_h;
        TTF_SizeText(
            m_fonts.at(font_size)->m_font.get(), text.data(), &text_w,
            &text_h);
        
        if (center_align) {
            rectangle.x -= static_cast<float>(text_w) /
                           static_cast<float>(canvas_size.h) /
                           2.0f / GetAspectRatio();
            rectangle.y -=
                static_cast<float>(text_h) / static_cast<float>(canvas_size.h) /
                2.0f;
        }
        
        auto scale = 1.0f;
        rectangle.x += rectangle.w / 2.0f - rectangle.w / 2.0f * scale;
        rectangle.y += rectangle.h / 2.0f - rectangle.h / 2.0f * scale;
        rectangle.w *= scale;
        rectangle.h *= scale;
        
        auto rid_gl_resource = m_rids_gl_resources.at(rid);
        
        _<ImageRenderer>().DrawImage(
            rid_gl_resource, unique_name_id, rectangle,
            false);
    }
    
    SizeF TextRenderer::MeasureString(std::string_view text,
                                        FontSizes font_size) const {
        auto font = m_fonts.at(font_size)->m_font;
        int text_w;
        int text_h;
        TTF_SizeText(font.get(), text.data(), &text_w, &text_h);
        auto canvas_size = GetCanvasSize();
        return {static_cast<float>(text_w) / canvas_size.w,
                static_cast<float>(text_h) / canvas_size.h};
    }
}