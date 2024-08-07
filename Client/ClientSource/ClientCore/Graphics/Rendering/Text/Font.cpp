/*
 * Font.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "Font.hpp"

namespace JoD {
    
    Font::Font(std::string_view fontFileName, int fontSize) {
        
        // Create main font object.
        m_font = std::unique_ptr<TTF_Font, SDLDeleter>(
            TTF_OpenFont(fontFileName.data(), fontSize));
        
        // Create outline font object.
        m_outlineFont = std::unique_ptr<TTF_Font, SDLDeleter>(
            TTF_OpenFont(fontFileName.data(), fontSize));
        
        // Set font outline width.
        TTF_SetFontOutline(m_outlineFont.get(), k_fontOutlineWidth);
    }
}