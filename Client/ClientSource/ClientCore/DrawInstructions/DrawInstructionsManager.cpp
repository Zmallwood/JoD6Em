/*
 * DrawInstructionsManager.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "DrawInstructionsManager.hpp"
#include "ClientCore/Graphics/Rendering/Images/ImageRenderer.hpp"
#include "ClientCore/Graphics/Rendering/Text/TextRenderer.hpp"

namespace JoD {
    
    DrawInstructionsManager::DrawInstructionsManager(){
        
        // Create a sufficient amount of RIDs for drawing images and game start.
        for (auto i = 0; i < k_maxNumImageDrawInstructions; i++) {
            
            m_ridsImages.push_back(_<ImageRenderer>().NewImage());
        }
        
        for (auto i = 0; i < k_maxNumTextDrawInstructions; i++) {
            
            m_ridsText.push_back(_<TextRenderer>().NewString());
        }
    }
    
    void DrawInstructionsManager::AddImageDrawInstruction(
        int imageNameHash,
        BoxF destination) {
        
        m_inactiveBuffer->emplace_back(
            DrawInstructionTypes::DrawImage,
            m_ridsImages.at(
                m_ridCounterImages
                ++),
            imageNameHash,
            destination);
    }
    
    
    void DrawInstructionsManager::AddTextDrawInstruction(
        std::string_view text, PointF position, bool centerAlign) {
        
        auto newInstruction = DrawInstruction {};
        
        newInstruction.rid = m_ridsText.at(m_ridCounterText++);
        newInstruction.type = DrawInstructionTypes::DrawText;
        newInstruction.text = text;
        newInstruction.position = position;
        newInstruction.centerAligned = centerAlign;
        
        m_inactiveBuffer->push_back(newInstruction);
    }
    
    void DrawInstructionsManager::ApplyBuffer() {
        
        const auto temp = m_activeBuffer;
        m_activeBuffer = m_inactiveBuffer;
        m_inactiveBuffer = temp;
        
        m_inactiveBuffer->clear();
        m_ridCounterImages = 0;
        m_ridCounterText = 0;
    }
    
    void DrawInstructionsManager::ExecuteInstructions() const {
        
        // Execute all drawing instructions that have been added.
        for (const auto &instruction : *m_activeBuffer){
            
            switch (instruction.type) {
            
            case DrawInstructionTypes::DrawImage: {
                
                _<ImageRenderer>().DrawImage(
                    instruction.rid,
                    instruction.imageNameHash,
                    instruction.destination);
                break;
            }
            case DrawInstructionTypes::DrawText: {
                
                _<TextRenderer>().DrawString(
                    instruction.rid, instruction.text,
                    instruction.position,
                    Colors::wheat,
                    instruction.centerAligned);
                break;
            }
            case DrawInstructionTypes::None: {
                
                break;
            }
            }
        }
    }
}