/*
 * expr_catch_all_exceptions.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class expr_catch_all_exceptions : public expr {
    public:
        expr_catch_all_exceptions(
            std::shared_ptr<expr> exception_handled_expression);
        
        expr_return_struct evaluate() override;
        
    private:
        std::shared_ptr<expr> m_exception_handled_expression;
    };
}