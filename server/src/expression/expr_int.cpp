/*
 * expr_int.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_int.h"

namespace jod {
    expr_int::expr_int(int int_value)
        : m_int_value(int_value) {
    }
    
    expr_return_struct expr_int::evaluate() {
        return {0, m_int_value};
    }
}