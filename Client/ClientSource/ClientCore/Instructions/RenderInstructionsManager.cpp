/*
 * RenderInstructionsManager.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderInstructionsManager.h"
#include "ClientCore/Graphics/Rendering/Images/ImageRenderer.h"
#include "ClientCore/Graphics/Rendering/Text/TextRenderer.h"
#include "ClientCore/Instructions/ImageDrawInstruction.h"
#include "ClientCore/Instructions/InstructionTypes.h"

namespace jod {
    render_instructions_manager::render_instructions_manager(){
        // Create a sufficient amount of RIDs for drawing images and game start.
        for (auto i = 0; i < k_max_num_draw_instructions; i++)
            m_rids.push_back(_<ImageRenderer>().NewImage());
        
        for (auto i = 0; i < k_max_num_draw_text_instructions; i++)
            m_rids_text.push_back(_<text_renderer>().new_string());
    }
    
    void render_instructions_manager::add_image_draw_instruction(
        int image_name_hash,
        rectf destination) {
        // Create a new image draw instruction and save it.
        auto new_instruction = image_draw_instruction{ instruction_types::image,
                                                       m_rids.at(
                                                           m_rid_counter_images
                                                           ++),
                                                       image_name_hash,
                                                       destination};
        m_image_draw_instructions_buffer.push_back(
            new_instruction);
    }
    
    
    void render_instructions_manager::add_text_draw_instruction(
        std::string_view text, pointf position) {
        auto new_instruction = image_draw_instruction {};
        new_instruction.rid = m_rids_text.at(m_rid_counter_text++);
        new_instruction.type = instruction_types::text;
        new_instruction.text = text;
        new_instruction.position = position;
        m_image_draw_instructions_buffer.push_back(new_instruction);
    }
    
    void render_instructions_manager::apply_buffer() {
        // Replace the current instruction group with the new one.
        m_image_draw_instructions = m_image_draw_instructions_buffer;
        // Prepare the next-instructions-set for storing a new set
        // of instructions by clearing it.
        m_image_draw_instructions_buffer.clear();
        m_rid_counter_images = 0;
        m_rid_counter_text = 0;
    }
    
    void render_instructions_manager::execute_instructions() {
        // Execute all drawing instructions that have been added.
        for (auto &instr : m_image_draw_instructions){
            switch (instr.type) {
            case instruction_types::image:
                _<ImageRenderer>().DrawImage(
                    instr.rid,
                    instr.image_name_hash,
                    instr.destination);
                break;
            case instruction_types::text:
                _<text_renderer>().draw_string(
                    instr.rid, instr.text,
                    instr.position);
                break;
            case instruction_types::none:
                break;
            }
        }
    }
}