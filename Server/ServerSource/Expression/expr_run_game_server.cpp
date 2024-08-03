/*
 * expr_run_game_server.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_run_game_server.h"
#include "expr_run_web_socket_server.h"
#include "expr_generate_new_world.h"
#include "expr_seed_randomization.h"
#include "expr_string.h"

namespace jod {
    expr_run_game_server::expr_run_game_server(
        std::shared_ptr<expr> expression_args)
        : m_expression_args(expression_args) {
        
    }
    
    expr_return_struct expr_run_game_server::eval() {
        if (auto result = expr_seed_randomization().eval().return_code)
            return {result};
        
        if (auto result = expr_generate_new_world().eval().return_code)
            return {result};
        
        auto args_data = m_expression_args->eval();
        
        if (auto result = args_data.return_code)
            return {result};
        
        auto [expression_socket_address, expression_socket_port] =
            std::any_cast<
                std::pair<std::shared_ptr<expr_string>,
                          std::shared_ptr<expr_string>>>(
                args_data.data);
        
        return expr_run_web_socket_server(
            expression_socket_address,
            expression_socket_port).eval();
    }
}