/*
 * expr_world_generation_generate_water.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class expr_world_generation_generate_water : public expr {
    public:
        expr_return_struct eval();
    };
}