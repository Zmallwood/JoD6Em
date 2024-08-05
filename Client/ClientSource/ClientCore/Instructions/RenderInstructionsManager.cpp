/*
 * RenderInstructionsManager.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "RenderInstructionsManager.hpp"
#include "ClientCore/Graphics/Rendering/Images/ImageRenderer.hpp"
#include "ClientCore/Graphics/Rendering/Text/TextRenderer.hpp"
#include "ClientCore/Instructions/ImageDrawInstruction.hpp"
#include "ClientCore/Instructions/InstructionTypes.hpp"

namespace JoD {
    
    RenderInstrutionsManager::RenderInstrutionsManager(){
        
        // Create a sufficient amount of RIDs for drawing images and game start.
        for (auto i = 0; i < k_maxNumDrawInstructions; i++) {
            
            m_rids.push_back(_<ImageRenderer>().NewImage());
        }
        
        for (auto i = 0; i < k_maxNumDrawTextInstructions; i++) {
            
            m_ridsText.push_back(_<TextRenderer>().NewString());
        }
    }
    
    void RenderInstrutionsManager::AddImageDrawInstruction(
        int imageNameHash,
        RectF destination) {
        
        m_inactiveBuffer->emplace_back(
            InstructionTypes::Image,
            m_rids.at(
                m_ridCounterImages
                ++),
            imageNameHash,
            destination);
    }
    
    
    void RenderInstrutionsManager::AddTextDrawInstruction(
        std::string_view text, PointF position) {
        
        auto newInstruction = ImageDrawInstruction {};
        
        newInstruction.rid = m_ridsText.at(m_ridCounterText++);
        newInstruction.type = InstructionTypes::Text;
        newInstruction.text = text;
        newInstruction.position = position;
        
        m_inactiveBuffer->push_back(newInstruction);
    }
    
    void RenderInstrutionsManager::ApplyBuffer() {
        
        auto temp = m_activeBuffer;
        m_activeBuffer = m_inactiveBuffer;
        m_inactiveBuffer = temp;
        
        m_inactiveBuffer->clear();
        m_ridCounterImages = 0;
        m_ridCounterText = 0;
    }
    
    void RenderInstrutionsManager::ExecuteInstructions() const {
        
        // Execute all drawing instructions that have been added.
        for (auto &instruction : *m_activeBuffer){
            
            switch (instruction.type) {
            
            case InstructionTypes::Image: {
                
                _<ImageRenderer>().DrawImage(
                    instruction.rid,
                    instruction.imageNameHash,
                    instruction.destination);
                break;
            }
            case InstructionTypes::Text: {
                
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