/*
 * expr_generate_new_world.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_generate_new_world.h"
#include "expr_world_generation_clear_with_grass.h"
#include "expr_world_generation_generate_water.h"

namespace jod {
    expr_return_struct expr_generate_new_world::evaluate() {
        return {expr_world_generation_clear_with_grass().evaluate().return_code
                ||
                expr_world_generation_generate_water().evaluate().return_code};
    }
}