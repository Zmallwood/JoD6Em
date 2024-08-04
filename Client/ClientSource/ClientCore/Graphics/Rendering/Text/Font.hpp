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
        /// @param font_file_name Font file name.
        /// @param font_size Font size used for this font object.
        Font(const std::string &font_file_name, int font_size);
        
        std::shared_ptr<TTF_Font> m_font; ///< Regular SDL font object.
        
        std::shared_ptr<TTF_Font> m_outline_font; ///< Outline SDL font object.
        
        static constexpr int k_font_outline_width{2}; ///< Font outline width.
    };
}