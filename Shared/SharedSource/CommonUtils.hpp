/*
 * CommonUtils.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include <string_view>

namespace JoD {
    
    template <class T>
    T &_() {
        
        static T instance;
        
        return instance;
    }
    
    int Hash(std::string_view text);
}