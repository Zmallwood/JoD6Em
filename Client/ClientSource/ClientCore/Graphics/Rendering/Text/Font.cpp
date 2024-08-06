/*
 * Font.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Font.hpp"

namespace JoD {
    
    Font::Font(std::string_view fontFileName, int fontSize) {
        
        // Create main font object.
        m_font = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(fontFileName.data(), fontSize), SDLDeleter());
        
        // Create outline font object.
        m_outlineFont = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(fontFileName.data(), fontSize), SDLDeleter());
        
        // Set font outline width.
        TTF_SetFontOutline(m_outlineFont.get(), k_fontOutlineWidth);
    }
}