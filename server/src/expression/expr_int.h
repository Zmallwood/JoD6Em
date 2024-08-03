/*
 * expr_int.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class expr_int : public expr {
    public:
        expr_int(int int_value);
        
        expr_return_struct evaluate();
        
    private:
        int m_int_value = 0;
    };
}