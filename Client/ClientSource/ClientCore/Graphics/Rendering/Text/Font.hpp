/*
 * Font.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

/// Font object used for text rendering.
class Font {
    
  public:
/// Construct a new font object.
/// @param fontFileName Font file name.
/// @param fontSize Font size used for this font object.
    Font(std::string_view fontFileName, int fontSize);
    
/// Get the regular font object used for text rendering.
/// @return TTF_Font* The regular font object.
    TTF_Font* GetFont() const {
        return m_font.get();
    }
    
/// Get the outline font object used for text outline rendering.
/// @return TTF_Font* The outline font object.
    TTF_Font* GetOutlineFont() const {
        return m_outlineFont.get();
    }
    
/// Get the constant value for font outline width.
/// @return constexpr int Font outline width.
    static constexpr int GetFontOutlineWidth() {
        return k_fontOutlineWidth;
    }
    
  private:
// Regular SDL font object.
    std::unique_ptr<TTF_Font, SDLDeleter> m_font;
// Outline SDL font object.
    std::unique_ptr<TTF_Font, SDLDeleter> m_outlineFont;
// Font outline width.
    static constexpr int k_fontOutlineWidth{2};
};
}
