/*
 * expr_string.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_string.h"

namespace jod {
    expr_string::expr_string(std::string_view string_value)
        : m_string_value(string_value) {
    }
    
    expr_return_struct expr_string::eval() {
        return {0, m_string_value};
    }
}