/*
 * expr_run_game_server.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class expr_run_game_server : public expr {
    public:
        expr_run_game_server(std::shared_ptr<expr> expression_args);
        
        expr_return_struct eval() override;
        
    private:
        std::shared_ptr<expr> m_expression_args;
    };
}