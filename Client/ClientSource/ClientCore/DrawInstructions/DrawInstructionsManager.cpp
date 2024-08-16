/*
 * DrawInstructionsManager.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "DrawInstructionsManager.hpp"
#include "ClientCore/Graphics/Rendering/Images/ImageRenderer.hpp"
#include "ClientCore/Graphics/Rendering/Text/TextRenderer.hpp"
#include "ImageDrawInstruction.hpp"
#include "TextDrawInstruction.hpp"

namespace JoD {
    
    DrawInstructionsManager::DrawInstructionsManager() {
        
        // Create a sufficient amount of RIDs for drawing images at game start.
        for (auto i = 0; i < k_maxNumImageDrawInstructions; i++) {
            
            m_ridsImages.push_back(_<ImageRenderer>().NewImage());
        }
        
        // Create a sufficient amount of RIDs for drawing text at game start.
        for (auto i = 0; i < k_maxNumTextDrawInstructions; i++) {
            
            m_ridsText.push_back(_<TextRenderer>().NewString());
        }
    }
    
    void DrawInstructionsManager::AddImageDrawInstruction(
        int imageNameHash,
        BoxF destination) {
        
        // Create empty image draw instruction.
        auto newInstr = std::make_unique<ImageDrawInstruction>();
        
        // Fill with data.
        newInstr->type = DrawInstructionTypes::DrawImage;
        newInstr->rid = m_ridsImages.at(
            m_ridCounterImages
            ++);
        newInstr->imageNameHash = imageNameHash;
        newInstr->destination = destination;
        
        // Add to inactive buffer.
        m_inactiveBuffer->push_back(std::move(newInstr));
    }
    
    
    void DrawInstructionsManager::AddTextDrawInstruction(
        std::string_view text, PointF position, bool centerAlign) {
        
        // Create empty text draw instruction.
        auto newInstr = std::make_unique<TextDrawInstruction>();
        
        // Fill with data.
        newInstr->rid = m_ridsText.at(m_ridCounterText++);
        newInstr->type = DrawInstructionTypes::DrawText;
        newInstr->text = text;
        newInstr->position = position;
        newInstr->centerAligned = centerAlign;
        
        // Add to inactive buffer.
        m_inactiveBuffer->push_back(std::move(newInstr));
    }
    
    void DrawInstructionsManager::ApplyBuffer() {
        
        // Swap active and inactive buffers.
        const auto temp = m_activeBuffer;
        m_activeBuffer = m_inactiveBuffer;
        m_inactiveBuffer = temp;
        
        // Reset state for inactive buffer and rid counters.
        m_inactiveBuffer->clear();
        m_ridCounterImages = 0;
        m_ridCounterText = 0;
    }
    
    void DrawInstructionsManager::ExecuteInstructions() const {
        
        // Execute all drawing instructions that have been added.
        for (const auto &instruction : *m_activeBuffer){
            
            switch (instruction->type) {
            
            case DrawInstructionTypes::DrawImage: {
                
                // Cast to image instruction type.
                auto casted =
                    static_cast<ImageDrawInstruction*>(instruction.get());
                
                // Draw image as specified in the instruction.
                _<ImageRenderer>().DrawImage(
                    casted->rid,
                    casted->imageNameHash,
                    casted->destination);
                
                break;
            }
            case DrawInstructionTypes::DrawText: {
                
                // Cast to text instruction type.
                auto casted =
                    static_cast<TextDrawInstruction*>(instruction.get());
                
                // Draw string as specified in the instruction.
                _<TextRenderer>().DrawString(
                    casted->rid, casted->text,
                    casted->position,
                    Colors::wheat,
                    casted->centerAligned);
                
                break;
            }
            case DrawInstructionTypes::None: {
                
                break;
            }
            }
        }
    }
}