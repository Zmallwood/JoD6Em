/*
 * TextRenderer.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "FontSizes.h"

namespace jod {
    class font;
    
    //! \brief Renderer used to allocated resources for, and render, text to the canvas.
    class text_renderer {
    public:
        //! \brief Construct a new text renderer object by initializing
        //!        font objects for different sizes.
        text_renderer();
        
        //! \brief Draw a text string to the canvas.
        //! \param rid Resource ID previously allocated.
        //! \param text Text string to render.
        //! \param position Position to render at in the canvas.
        //! \param color Color of the rendered text.
        //! \param center_align Specifies if text should be center aligned.
        //! \param font_size Font size of the rendered text.
        void draw_string(rid rid, std::string_view text, pointf position,
                         colorf color = {1.0f, 1.0f, 1.0f, 1.0f},
                         bool center_align = false,
                         font_sizes font_size = font_sizes::_20);
        
        //! \brief Allocate resources for a text string to be rendered.
        //! \return rid Resource ID for the allocated resources.
        rid new_string();
        
        //! \brief Measure a text string with specified size and return its dimensions.
        //! \param text Text string to be measured.
        //! \param font_size Font size to measure with.
        //! \return sizef Text string dimensions.
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