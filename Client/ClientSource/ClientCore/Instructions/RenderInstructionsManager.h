/*
 * RenderInstructionsManager.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ImageDrawInstruction.h"

namespace jod {   
    //! \brief Holds latest set of rendering instructions and executes them.
    class render_instructions_manager {
    public:
        //! \brief Construct a new Render Instructions Manager object.
        render_instructions_manager();
        
        //! \brief Add new image draw instruction to group, called on request from server.
        //! \param image_name_hash Hash code of image name to draw.
        //! \param destination Destination rectangle to draw the image at.
        void add_image_draw_instruction(int image_name_hash, rectf destination);

        void add_text_draw_instruction(std::string_view text, pointf position);
        
        //! \brief Copies the buffered render instructions to the active render instructions set.
        void apply_buffer();
        
        //! \brief Performs all rendering instructions by performing rendering instructions to the
        //!        web browser.
        void execute_instructions();
        
    private:
        std::vector<image_draw_instruction>
        m_image_draw_instructions; //!< Holds the image draw instructions that are executed each call to DrawCanvas().
        
        std::vector<image_draw_instruction>
        m_image_draw_instructions_buffer; //!< Holds the buffer for the next set of draw of instructions.
        
        std::vector<rid> m_rids; //!< A set of preallocated RIDs used for drawing images, created in the constructor.

        std::vector<rid> m_rids_text;

        int m_rid_counter_images = 0;
        int m_rid_counter_text = 0;
        
        const int k_max_num_draw_instructions = 1000; //!< No more images than this value can be rendererd in a single game frame.
        
        const int k_max_num_draw_text_instructions = 100; //!< No more images than this value can be rendererd in a single game frame.
    };
}