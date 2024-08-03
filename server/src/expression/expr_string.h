/*
 * expr_string.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class expr_string : public expr {
    public:
        expr_string(std::string_view string_value);

        expr_return_struct evaluate();
        
    private:
        std::string m_string_value;
    };
}