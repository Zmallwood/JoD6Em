/*
 * DrawInstructionsManager.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "IDrawInstruction.hpp"

namespace JoD {

class DrawInstructionsManager {
    
  public:
    DrawInstructionsManager();
    
    void AddImageDrawInstruction(
        int imageNameHash, BoxF destination,
        bool repeatTexture,
        SizeF textureFillAmount = {1.0f, 1.0f});
    
    void AddTextDrawInstruction
        (std::string_view text, PointF position,
        bool centerAlign);
    
    void ApplyBuffer();
    
    void ExecuteInstructions() const;
    
  private:
    std::vector<std::unique_ptr<IDrawInstruction>>
    m_drawInstructionsBuffer1;
    std::vector<std::unique_ptr<IDrawInstruction>>
    m_drawInstructionsBuffer2;
    std::vector<std::unique_ptr<IDrawInstruction>>* m_activeBuffer {
        &m_drawInstructionsBuffer1};
    std::vector<std::unique_ptr<IDrawInstruction>>* m_inactiveBuffer {
        &m_drawInstructionsBuffer2};
    std::vector<RID> m_ridsImages;
    std::vector<RID> m_ridsText;
    int m_ridCounterImages {0};
    int m_ridCounterText {0};
    const int k_maxNumImageDrawInstructions {6000};
    const int k_maxNumTextDrawInstructions {100};
};
}
