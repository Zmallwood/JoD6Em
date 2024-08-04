/*
 * Font.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Font.hpp"

namespace JoD {
    Font::Font(const std::string &font_file_name, int font_size) {
        m_font = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(font_file_name.c_str(), font_size), SDLDeleter());
        m_outline_font = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(font_file_name.c_str(), font_size), SDLDeleter());
        
        TTF_SetFontOutline(m_outline_font.get(), k_font_outline_width);
    }
}