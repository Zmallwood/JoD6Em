/*
 * DrawInstructionsManager.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "DrawInstructionsManager.hpp"
#include "ClientCore/Graphics/Rendering/Images/ImageRenderer.hpp"
#include "ClientCore/Graphics/Rendering/Text/TextRenderer.hpp"
#include "ImageDrawInstruction.hpp"
#include "TextDrawInstruction.hpp"

namespace JoD {

DrawInstructionsManager::DrawInstructionsManager() {
    
    for (auto i = 0; i < k_maxNumImageDrawInstructions; i++)
        m_ridsImages.push_back(_<ImageRenderer>().NewImage());
    
    for (auto i = 0; i < k_maxNumTextDrawInstructions; i++)
        m_ridsText.push_back(_<TextRenderer>().NewString());
}

void DrawInstructionsManager::AddImageDrawInstruction(
    int imageNameHash, BoxF destination, bool repeatTexture,
    SizeF textureFillAmount) {
    
    auto newInstr = std::make_unique<ImageDrawInstruction>();
    
    newInstr->type = DrawInstructionTypes::DrawImage;
    newInstr->rid = m_ridsImages.at(m_ridCounterImages++);
    newInstr->imageNameHash = imageNameHash;
    newInstr->destination = destination;
    newInstr->repeatTexture = repeatTexture;
    newInstr->textureFillAmount = textureFillAmount;
    
    m_inactiveBuffer->push_back(std::move(newInstr));
}

void DrawInstructionsManager::AddTextDrawInstruction(
    std::string_view text, PointF position, bool centerAlign) {
    
    auto newInstr = std::make_unique<TextDrawInstruction>();
    
    newInstr->rid = m_ridsText.at(m_ridCounterText++);
    newInstr->type = DrawInstructionTypes::DrawText;
    newInstr->text = text;
    newInstr->position = position;
    newInstr->centerAligned = centerAlign;
    
    m_inactiveBuffer->push_back(std::move(newInstr));
}

void DrawInstructionsManager::ApplyBuffer() {
    
    auto temp = m_activeBuffer;
    m_activeBuffer = m_inactiveBuffer;
    m_inactiveBuffer = temp;
    
    m_inactiveBuffer->clear();
    m_ridCounterImages = 0;
    m_ridCounterText = 0;
}

void DrawInstructionsManager::ExecuteInstructions() const {
    
    for (const auto &instruction : *m_activeBuffer) {
        
        switch (instruction->type) {
        
        case DrawInstructionTypes::DrawImage: {
            
            auto casted =
                static_cast<ImageDrawInstruction*>(instruction.get());
            
            _<ImageRenderer>().DrawImage(
                casted->rid,
                casted->imageNameHash,
                casted->destination,
                casted->repeatTexture,
                casted->textureFillAmount);
            
            break;
        }
        case DrawInstructionTypes::DrawText: {
            
            auto casted =
                static_cast<TextDrawInstruction*>(instruction.get());
            
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
