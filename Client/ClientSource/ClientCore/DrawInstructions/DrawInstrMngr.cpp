/*
 * DrawInstrMngr.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "DrawInstrMngr.hpp"
#include "ClientCore/Graphics/Rendering/Images/ImageRenderer.hpp"
#include "ClientCore/Graphics/Rendering/Text/TextRenderer.hpp"
#include "ImageDrawInstr.hpp"
#include "TextDrawInstr.hpp"

namespace JoD {

DrawInstrMngr::DrawInstrMngr() {
    
    for (auto i = 0; i < k_maxNumImageDrawInstr; i++)
        m_ridsImages.push_back(_<ImageRenderer>().NewImg());
    
    for (auto i = 0; i < k_maxNumTextDrawInstr; i++)
        m_ridsText.push_back(_<TextRenderer>().NewString());
}

void DrawInstrMngr::AddImageDrawInst(int imgNameHash, BoxF dest,
                                     bool repeatTex, SizeF texFillAmount) {
    
    auto newInstr = std::make_unique<ImageDrawInstr>();
    
    newInstr->type = DrawInstrTypes::DrawImage;
    newInstr->rid = m_ridsImages.at(m_ridCounterImages++);
    newInstr->imgNameHash = imgNameHash;
    newInstr->dest = dest;
    newInstr->repeatTex = repeatTex;
    newInstr->texFillAmount = texFillAmount;
    
    m_inactiveBuff->push_back(std::move(newInstr));
}

void DrawInstrMngr::AddTextDrawInstr(std::string_view text, PointF pos,
                                     bool centered) {
    
    auto newInstr = std::make_unique<TextDrawInstr>();
    
    newInstr->rid = m_ridsText.at(m_ridCounterText++);
    newInstr->type = DrawInstrTypes::DrawText;
    newInstr->text = text;
    newInstr->position = pos;
    newInstr->centered = centered;
    
    m_inactiveBuff->push_back(std::move(newInstr));
}

void DrawInstrMngr::ApplyBuffer() {
    
    auto tmp = m_activeBuff;
    m_activeBuff = m_inactiveBuff;
    m_inactiveBuff = tmp;
    
    m_inactiveBuff->clear();
    m_ridCounterImages = 0;
    m_ridCounterText = 0;
}

void DrawInstrMngr::ExecAllInstr() const {
    
    for (const auto &instr : *m_activeBuff) {
        
        switch (instr->type) {
        
        case DrawInstrTypes::DrawImage: {
            
            auto casted = static_cast<ImageDrawInstr*>(instr.get());
            
            _<ImageRenderer>().DrawImg(
                casted->rid,
                casted->imgNameHash,
                casted->dest,
                casted->repeatTex,
                casted->texFillAmount);
            
            break;
        }
        case DrawInstrTypes::DrawText: {
            
            auto casted = static_cast<TextDrawInstr*>(instr.get());
            
            _<TextRenderer>().DrawString(
                casted->rid, casted->text,
                casted->position,
                Colors::wheat,
                casted->centered);
            
            break;
        }
        case DrawInstrTypes::None: {
            
            break;
        }
        }
    }
}
}
