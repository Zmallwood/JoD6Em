/*
 * expr_generate_new_world.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class expr_generate_new_world : public expr {
    public:
        expr_return_struct eval() override;
    };
}