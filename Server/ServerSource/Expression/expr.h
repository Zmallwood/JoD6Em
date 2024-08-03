/*
 * expression.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class expr {
    public:
        virtual expr_return_struct eval() = 0;
    };
}