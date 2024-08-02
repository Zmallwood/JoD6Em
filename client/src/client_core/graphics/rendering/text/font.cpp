/*
 * font.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "font.h"

namespace jod {
    font::font(const std::string &font_file_name, int font_size) {
        m_font = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(font_file_name.c_str(), font_size), sdl_deleter());
        m_outline_font = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(font_file_name.c_str(), font_size), sdl_deleter());
        
        TTF_SetFontOutline(m_outline_font.get(), k_font_outline_width);
    }
}