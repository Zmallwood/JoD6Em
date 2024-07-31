// Copyright (c) 2024 Andreas Åkerberg.
#pragma once
#include <string_view>
namespace jod {
    template <class T>
    T &
    _(){
        static T instance;
        return instance;
    }
    
    int hash(
        std::string_view text);
}