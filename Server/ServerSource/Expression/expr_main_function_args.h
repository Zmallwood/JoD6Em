/*
 * expr_main_function_args.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class expr_main_function_args : public expr {
    public:
        expr_main_function_args(int argc, char** argv);
        
        expr_return_struct eval() override;
        
    private:
        int m_argc;
        char **m_argv;
    };
}