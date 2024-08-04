/*
 * RenderInstructionsManager.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ImageDrawInstruction.hpp"

namespace JoD {   
    /// @brief Holds latest set of rendering instructions and executes them.
    class RenderInstrutionsManager {
    public:
        /// @brief Construct a new Render Instructions Manager object.
        RenderInstrutionsManager();
        
        /// @brief Add new image draw instruction to group, called on request from server.
        /// @param image_name_hash Hash code of image name to draw.
        /// @param destination Destination rectangle to draw the image at.
        void AddImageDrawInstruction(int image_name_hash, RectF destination);

        void AddTextDrawInstruction(std::string_view text, PointF position);
        
        /// @brief Copies the buffered render instructions to the active render instructions set.
        void ApplyBuffer();
        
        /// @brief Performs all rendering instructions by performing rendering instructions to the
        ///        web browser.
        void ExecuteInstructions();
        
    private:
        std::vector<ImageDrawInstruction>
        m_image_draw_instructions; ///< Holds the image draw instructions that are executed each call to DrawCanvas().
        
        std::vector<ImageDrawInstruction>
        m_image_draw_instructions_buffer; ///< Holds the buffer for the next set of draw of instructions.
        
        std::vector<RID> m_rids; ///< A set of preallocated RIDs used for drawing images, created in the constructor.

        std::vector<RID> m_rids_text;

        int m_rid_counter_images = 0;
        
        int m_rid_counter_text = 0;
        
        const int k_max_num_draw_instructions = 1000; ///< No more images than this value can be rendererd in a single game frame.
        
        const int k_max_num_draw_text_instructions = 100; ///< No more images than this value can be rendererd in a single game frame.
    };
}