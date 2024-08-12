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
#include <memory>

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
        
        auto newInstruction = std::make_unique<ImageDrawInstruction>();
        
        newInstruction->type = DrawInstructionTypes::DrawImage;
        newInstruction->rid = m_ridsImages.at(
                m_ridCounterImages
                ++);
        newInstruction->imageNameHash = imageNameHash;
        newInstruction->destination = destination;
        
        m_inactiveBuffer->push_back(std::move(newInstruction));
    }
    
    
    void DrawInstructionsManager::AddTextDrawInstruction(
        std::string_view text, PointF position, bool centerAlign) {
        
        auto newInstruction = std::make_unique<TextDrawInstruction>();
        
        newInstruction->rid = m_ridsText.at(m_ridCounterText++);
        newInstruction->type = DrawInstructionTypes::DrawText;
        newInstruction->text = text;
        newInstruction->position = position;
        newInstruction->centerAligned = centerAlign;
        
        m_inactiveBuffer->push_back(std::move(newInstruction));
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
            
            switch (instruction->type) {
            
            case DrawInstructionTypes::DrawImage: {
                
                auto casted = static_cast<ImageDrawInstruction*>(instruction.get());
                
                _<ImageRenderer>().DrawImage(
                    casted->rid,
                    casted->imageNameHash,
                    casted->destination);
                break;
            }
            case DrawInstructionTypes::DrawText: {
                
                auto casted = static_cast<TextDrawInstruction*>(instruction.get());
                
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