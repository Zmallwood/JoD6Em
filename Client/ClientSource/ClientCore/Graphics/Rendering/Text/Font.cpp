/*
 * Font.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Font.hpp"

namespace JoD {
    
    Font::Font(std::string_view fontFileName, int fontSize) {
        
        m_font = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(fontFileName.data(), fontSize), SDLDeleter());
        m_outlineFont = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(fontFileName.data(), fontSize), SDLDeleter());
        
        TTF_SetFontOutline(m_outlineFont.get(), k_fontOutlineWidth);
    }
}