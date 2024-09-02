/*
 * DrawInstrMngr.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "IDrawInstr.hpp"

namespace JoD {

class DrawInstrMngr {
    
  public:
    DrawInstrMngr();
    void AddImageDrawInst(int imgNameHash, BoxF dest, bool repeatTex,
                          SizeF texFillAmount = {1.0f, 1.0f});
    void AddTextDrawInstr(std::string_view text, PointF pos, bool centered);
    void ApplyBuffer();
    void ExecAllInstr() const;
    
  private:
    std::vector<std::unique_ptr<IDrawInstr>> m_drawInstrBuff1;
    std::vector<std::unique_ptr<IDrawInstr>> m_drawInstrBuff2;
    std::vector<std::unique_ptr<IDrawInstr>>* m_activeBuff {&m_drawInstrBuff1};
    std::vector<std::unique_ptr<IDrawInstr>>* m_inactiveBuff {&m_drawInstrBuff2};
    std::vector<RID> m_ridsImages;
    std::vector<RID> m_ridsText;
    int m_ridCounterImages {0};
    int m_ridCounterText {0};
    const int k_maxNumImageDrawInstr {6000};
    const int k_maxNumTextDrawInstr {100};
};
}
