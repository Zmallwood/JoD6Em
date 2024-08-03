/*
 * expr_return_object.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    struct expr_return_struct {
        int return_code = 0;
        std::any data;
    };
}