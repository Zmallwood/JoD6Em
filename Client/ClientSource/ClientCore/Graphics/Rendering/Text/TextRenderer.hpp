/*
 * TextRenderer.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "FontSizes.hpp"

namespace JoD {
    
    class Font;
    
    ///
    /// Renderer used to allocated resources for, and render, text to the canvas.
    ///
    class TextRenderer {
        
      public:
        ///
        /// Construct a new text renderer object by initializing
        /// font objects for different sizes.
        ///
        TextRenderer();
        
        ///
        /// Draw a text string to the canvas.
        ///
        /// @param rid Resource ID previously allocated.
        /// @param text Text string to render.
        /// @param position Position to render at in the canvas.
        /// @param color Color of the rendered text.
        /// @param centerAlign Specifies if text should be center aligned.
        /// @param fontSize Font size of the rendered text.
        ///
        void DrawString(
            RID rid, std::string_view text, PointF position,
            ColorF color = {1.0f, 1.0f, 1.0f, 1.0f},
            bool centerAlign = false,
            FontSizes fontSize = FontSizes::_20) const;
        
        ///
        /// Allocate resources for a text string to be rendered.
        ///
        /// @return rid Resource ID for the allocated resources.
        ///
        RID NewString();
        
        ///
        /// Measure a text string with specified size and return its dimensions.
        ///
        /// @param text Text string to be measured.
        /// @param fontSize Font size to measure with.
        /// @return sizef Text string dimensions.
        ///
        SizeF MeasureString(std::string_view text, FontSizes fontSize) const;
        
      private:
        ///
        /// Does the actual rendering operations when drawing a string.
        ///
        /// @param rid Resource ID previously allocated for the string.
        /// @param text Text to draw to the canvas.
        /// @param color Color of the text to draw.
        /// @param centerAlign If the text should be center aligned or not.
        /// @param fontSize Size of font to use.
        /// @param out_uniqueNameID Outputs image name for the rendered text texture.
        /// @param out_dimensions Output dimensions of the rendered text texture.
        ///
        void RenderText(
            RID rid, std::string_view text, ColorF color,
            bool centerAlign, FontSizes fontSize,
            std::string &out_uniqueNameID,
            SizeF &out_dimensions) const;
        
        std::map<FontSizes, std::shared_ptr<const Font>> m_fonts; ///< Stored font objects of different sizes.
        std::map<RID, std::string> m_uniqueNameIDs; ///< Unique names of images created to render text.
        std::map<RID, RID> m_ridsGLResources; ///< Map where key is imageID and value is RID used with ImageRenderer.
        const std::string k_relFontsPath{"Resources/Fonts/"}; ///< File system path to fonts location.
        const ColorF k_outlineColor{0.0f, 0.0f, 0.0f, 1.0f}; ///< Color of outline of all rendered text.
    };
}