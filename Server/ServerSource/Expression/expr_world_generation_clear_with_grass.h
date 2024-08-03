/*
 * expr_world_generation_clear_with_grass.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class expr_world_generation_clear_with_grass : expr {
    public:
        expr_return_struct eval();
    };
}