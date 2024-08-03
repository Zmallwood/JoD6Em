/*
 * expr_seed_randomization.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_seed_randomization.h"

namespace jod {
    expr_return_struct expr_seed_randomization::evaluate() {
        srand(time(0));
        return {0};
    }
}