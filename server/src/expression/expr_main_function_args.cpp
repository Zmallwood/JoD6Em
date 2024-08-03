/*
 * expr_main_function_args.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_main_function_args.h"
#include "expr_string.h"

namespace jod {
    expr_main_function_args::expr_main_function_args(
        int argc,
        char **argv)
        : m_argc(argc), m_argv(argv){
    }
    
    expr_return_struct expr_main_function_args::evaluate() {
        if (m_argc != 3){
            std::cerr << "Usage: JoDServer <address> <port>\n"
                      << "Example:\n"
                      << "    JoDServer 0.0.0.0 8080\n";
            return {1};
        }
        return {0, std::pair<std::shared_ptr<expr_string>,
                             std::shared_ptr<expr_string>>(
                    std::make_shared<expr_string>(m_argv[1]),
                    std::make_shared<expr_string>(m_argv[2]))};
    }
}