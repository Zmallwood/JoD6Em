/*
 * Font.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    /// @brief Font object used for text rendering.
    class Font {
    public:
        /// @brief Construct a new font object.
        /// @param fontFileName Font file name.
        /// @param fontSize Font size used for this font object.
        Font(std::string_view fontFileName, int fontSize);
        
        std::shared_ptr<TTF_Font> m_font; ///< Regular SDL font object.
        
        std::shared_ptr<TTF_Font> m_outlineFont; ///< Outline SDL font object.
        
        static constexpr int k_fontOutlineWidth{2}; ///< Font outline width.
    };
}