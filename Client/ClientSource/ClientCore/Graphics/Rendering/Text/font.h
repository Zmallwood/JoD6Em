/*
 * font.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    //! \brief Font object used for text rendering.
    class font {
    public:
        //! \brief Construct a new font object.
        //! \param font_file_name Font file name.
        //! \param font_size Font size used for this font object.
        font(const std::string &font_file_name, int font_size);
        
        std::shared_ptr<TTF_Font> m_font; //!< Regular SDL font object.
        
        std::shared_ptr<TTF_Font> m_outline_font; //!< Outline SDL font object.
        
        static constexpr int k_font_outline_width{2}; //!< Font outline width.
    };
}