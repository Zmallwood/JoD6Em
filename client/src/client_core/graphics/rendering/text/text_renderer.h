/*
 * text_renderer.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "font_sizes.h"
#include <string_view>

namespace jod {
    class font;
    
    class text_renderer {
    public:
        text_renderer();
        
        void draw_string(rid rid, std::string_view text, pointf position,
                         colorf color = {1.0f, 1.0f, 1.0f, 1.0f},
                         bool center_align = false,
                         font_sizes font_size = font_sizes::_20);
        
        rid new_string();
        
        sizef measure_string(std::string_view text, font_sizes font_size) const;
        
    private:
        void render_text(rid rid, std::string_view text, colorf color,
                         bool center_align, font_sizes font_size,
                         std::string &out_unique_name_id,
                         sizef &out_size) const;
        
        const std::string k_rel_fonts_path{"Resources/Fonts/"};
        
        const colorf k_outline_color{0.0f, 0.0f, 0.0f, 1.0f};
        
        std::map<font_sizes, std::shared_ptr<font> > m_fonts;
        
        std::map<rid, std::string> m_unqiue_name_ids;
        
        std::map<rid, rid> m_rids_gl_resources;
    };
}