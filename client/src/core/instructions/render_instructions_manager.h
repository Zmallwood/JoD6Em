// render_instructions_manager.h
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
///////////////////////////////////////////////////////////

#pragma once

#include "image_draw_instruction.h"

namespace jod {   
    //! \brief Holds latest set of rendering instructions and executes them.
    class render_instructions_manager {
    public:
        //! \brief Construct a new Render Instructions Manager object.
        render_instructions_manager();
        
        //! \brief Add new image draw instruction to group, called on request from server.
        //! \param imageNameHash Hash code of image name to draw.
        //! \param dest Destination rectangle to draw the image at.
        void add_image_draw_instruction(int imageNameHash, rectf dest);
        
        //! \brief Copies the buffered render instructions to the active render instructions set.
        void apply_buffer();
        
        //! \brief Performs all rendering instructions by performing rendering instructions to the
        //!        web browser.
        void execute_instructions();
        
    private:
        std::vector<image_draw_instruction>
        m_imageDrawInstructions; //!< Holds the image draw instructions that are executed each call to DrawCanvas().
        
        std::vector<image_draw_instruction>
        m_imageDrawInstructionsBuffer; //!< Holds the buffer for the next set of draw of instructions.
        
        std::vector<rid> m_rids; //!< A set of preallocated RIDs used for drawing images, created in the constructor.
        
        const int k_maxNumDrawInstructions = 1000; //!< No more images than this value can be rendererd in a single game frame.
    };
}