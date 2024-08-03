/*
 * expr_seed_randomization.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class expr_seed_randomization : public expr {
    public:
        expr_return_struct eval() override;
    };
}