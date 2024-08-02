/*
 * render_instructions_manager.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "render_instructions_manager.h"
#include "client_core/graphics/rendering/images/image_renderer.h"

namespace jod {
    render_instructions_manager::render_instructions_manager(){
        // Create a sufficient amount of RIDs for drawing images and game start.
        for (auto i = 0; i < k_maxNumDrawInstructions; i++)
            m_rids.push_back(_<image_renderer>().new_image());
    }
    
    void
    render_instructions_manager::add_image_draw_instruction(
        int imageNameHash,
        rectf dest) {
        // Create a new image draw instruction and save it.
        auto newInstruction = image_draw_instruction{
            m_rids.at(m_imageDrawInstructionsBuffer.size()),
            imageNameHash, dest};
        m_imageDrawInstructionsBuffer.push_back(
            newInstruction);
    }
    
    void
    render_instructions_manager::apply_buffer(){
        // Replace the current instruction group with the new one.
        m_imageDrawInstructions = m_imageDrawInstructionsBuffer;
        // Prepare the next-instructions-set for storing a new set
        // of instructions by clearing it.
        m_imageDrawInstructionsBuffer.clear();
    }
    
    void
    render_instructions_manager::execute_instructions(){
        // Execute all drawing instructions that have been added.
        for (auto &instr : m_imageDrawInstructions)
            _<image_renderer>().draw_image(
                instr.rid,
                instr.imageNameHash,
                instr.dest);
    }
}