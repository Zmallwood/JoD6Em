/*
 * font.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class font {
    public:
        font(const std::string &font_file_name, int font_size);
        
        std::shared_ptr<TTF_Font> m_font;
        
        std::shared_ptr<TTF_Font> m_outline_font;
        
        static constexpr int k_font_outline_width{2};
    };
}