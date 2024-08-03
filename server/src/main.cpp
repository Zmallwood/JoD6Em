/*
 * main.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expression/expr_run_game_server.h"
#include "expression/expr_main_function_args.h"
#include "expression/expr_catch_all_exceptions.h"

int main(int argc, char *argv[]) {
    using namespace jod;
    return expr_catch_all_exceptions(
        std::make_shared<expr_run_game_server>(
            std::make_shared<expr_main_function_args>(
                argc,
                argv))).eval().return_code;
}