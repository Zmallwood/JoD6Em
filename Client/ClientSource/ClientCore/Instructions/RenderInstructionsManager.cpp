/*
 * RenderInstructionsManager.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderInstructionsManager.hpp"
#include "ClientCore/Graphics/Rendering/Images/ImageRenderer.hpp"
#include "ClientCore/Graphics/Rendering/Text/TextRenderer.hpp"
#include "ClientCore/Instructions/DrawInstruction.hpp"
#include "ClientCore/Instructions/InstructionTypes.hpp"

namespace JoD {
    
    RenderInstructionsManager::RenderInstructionsManager(){
        
        // Create a sufficient amount of RIDs for drawing images and game start.
        for (auto i = 0; i < k_maxNumImageDrawInstructions; i++) {
            
            m_ridsImages.push_back(_<ImageRenderer>().NewImage());
        }
        
        for (auto i = 0; i < k_maxNumTextDrawInstructions; i++) {
            
            m_ridsText.push_back(_<TextRenderer>().NewString());
        }
    }
    
    void RenderInstructionsManager::AddImageDrawInstruction(
        int imageNameHash,
        BoxF destination) {
        
        m_inactiveBuffer->emplace_back(
            InstructionTypes::DrawImage,
            m_ridsImages.at(
                m_ridCounterImages
                ++),
            imageNameHash,
            destination);
    }
    
    
    void RenderInstructionsManager::AddTextDrawInstruction(
        std::string_view text, PointF position) {
        
        auto newInstruction = DrawInstruction {};
        
        newInstruction.rid = m_ridsText.at(m_ridCounterText++);
        newInstruction.type = InstructionTypes::DrawText;
        newInstruction.text = text;
        newInstruction.position = position;
        
        m_inactiveBuffer->push_back(newInstruction);
    }
    
    void RenderInstructionsManager::ApplyBuffer() {
        
        auto temp = m_activeBuffer;
        m_activeBuffer = m_inactiveBuffer;
        m_inactiveBuffer = temp;
        
        m_inactiveBuffer->clear();
        m_ridCounterImages = 0;
        m_ridCounterText = 0;
    }
    
    void RenderInstructionsManager::ExecuteInstructions() const {
        
        // Execute all drawing instructions that have been added.
        for (auto &instruction : *m_activeBuffer){
            
            switch (instruction.type) {
            
            case InstructionTypes::DrawImage: {
                
                _<ImageRenderer>().DrawImage(
                    instruction.rid,
                    instruction.imageNameHash,
                    instruction.destination);
                break;
            }
            case InstructionTypes::DrawText: {
                
                _<TextRenderer>().DrawString(
                    instruction.rid, instruction.text,
                    instruction.position);
                break;
            }
            case InstructionTypes::None: {
                
                break;
            }
            }
        }
    }
}