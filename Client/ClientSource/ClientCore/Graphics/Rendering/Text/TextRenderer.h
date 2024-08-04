/*
 * TextRenderer.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "FontSizes.h"

namespace JoD {
    class Font;
    
    /// @brief Renderer used to allocated resources for, and render, text to the canvas.
    class TextRenderer {
    public:
        /// @brief Construct a new text renderer object by initializing
        ///        font objects for different sizes.
        TextRenderer();
        
        /// @brief Draw a text string to the canvas.
        /// @param rid Resource ID previously allocated.
        /// @param text Text string to render.
        /// @param position Position to render at in the canvas.
        /// @param color Color of the rendered text.
        /// @param center_align Specifies if text should be center aligned.
        /// @param font_size Font size of the rendered text.
        void DrawString(RID rid, std::string_view text, PointF position,
                         ColorF color = {1.0f, 1.0f, 1.0f, 1.0f},
                         bool center_align = false,
                         FontSizes font_size = FontSizes::_20);
        
        /// @brief Allocate resources for a text string to be rendered.
        /// @return rid Resource ID for the allocated resources.
        RID NewString();
        
        /// @brief Measure a text string with specified size and return its dimensions.
        /// @param text Text string to be measured.
        /// @param font_size Font size to measure with.
        /// @return sizef Text string dimensions.
        SizeF MeasureString(std::string_view text, FontSizes font_size) const;
        
    private:
        void RenderText(RID rid, std::string_view text, ColorF color,
                         bool center_align, FontSizes font_size,
                         std::string &out_unique_name_id,
                         SizeF &out_size) const;
        
        const std::string k_rel_fonts_path{"Resources/Fonts/"};
        
        const ColorF k_outline_color{0.0f, 0.0f, 0.0f, 1.0f};
        
        std::map<FontSizes, std::shared_ptr<Font> > m_fonts;
        
        std::map<RID, std::string> m_unqiue_name_ids;
        
        std::map<RID, RID> m_rids_gl_resources;
    };
}