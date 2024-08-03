/*
 * expr_catch_all_exceptions.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_catch_all_exceptions.h"

namespace jod {
    
    expr_catch_all_exceptions::expr_catch_all_exceptions(
        std::shared_ptr<expr> exception_handled_expression)
        : m_exception_handled_expression(exception_handled_expression) {
        
    }
    
    expr_return_struct expr_catch_all_exceptions::eval() {
        try{
            return m_exception_handled_expression->eval();
        }
        catch (const std::exception &e){
            std::cerr << "Error: " << e.what() << std::endl;
            return {1};
        }
    }
}