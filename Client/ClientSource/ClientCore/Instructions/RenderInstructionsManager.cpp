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

namespace JoD {
    RenderInstrutionsManager::RenderInstrutionsManager(){
        // Create a sufficient amount of RIDs for drawing images and game start.
        for (auto i = 0; i < k_max_num_draw_instructions; i++)
            m_rids.push_back(_<ImageRenderer>().NewImage());
        
        for (auto i = 0; i < k_max_num_draw_text_instructions; i++)
            m_rids_text.push_back(_<TextRenderer>().NewString());
    }
    
    void RenderInstrutionsManager::AddImageDrawInstruction(
        int image_name_hash,
        RectF destination) {
        // Create a new image draw instruction and save it.
        auto new_instruction = ImageDrawInstruction{ InstructionTypes::image,
                                                       m_rids.at(
                                                           m_rid_counter_images
                                                           ++),
                                                       image_name_hash,
                                                       destination};
        m_image_draw_instructions_buffer.push_back(
            new_instruction);
    }
    
    
    void RenderInstrutionsManager::AddTextDrawInstruction(
        std::string_view text, PointF position) {
        auto new_instruction = ImageDrawInstruction {};
        new_instruction.rid = m_rids_text.at(m_rid_counter_text++);
        new_instruction.type = InstructionTypes::text;
        new_instruction.text = text;
        new_instruction.position = position;
        m_image_draw_instructions_buffer.push_back(new_instruction);
    }
    
    void RenderInstrutionsManager::ApplyBuffer() {
        // Replace the current instruction group with the new one.
        m_image_draw_instructions = m_image_draw_instructions_buffer;
        // Prepare the next-instructions-set for storing a new set
        // of instructions by clearing it.
        m_image_draw_instructions_buffer.clear();
        m_rid_counter_images = 0;
        m_rid_counter_text = 0;
    }
    
    void RenderInstrutionsManager::ExecuteInstructions() {
        // Execute all drawing instructions that have been added.
        for (auto &instr : m_image_draw_instructions){
            switch (instr.type) {
            case InstructionTypes::image:
                _<ImageRenderer>().DrawImage(
                    instr.rid,
                    instr.image_name_hash,
                    instr.destination);
                break;
            case InstructionTypes::text:
                _<TextRenderer>().DrawString(
                    instr.rid, instr.text,
                    instr.position);
                break;
            case InstructionTypes::none:
                break;
            }
        }
    }
}