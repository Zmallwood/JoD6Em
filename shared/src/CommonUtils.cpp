// Copyright (c) 2024 Andreas Åkerberg.
#include "CommonUtils.h"

namespace jod {
    int
    Hash(std::string_view text){
        unsigned long hash = 5381;
        for (size_t i = 0; i < text.size(); ++i)
            hash = 33 * hash + (unsigned char)text[i];
        return static_cast<int>(hash);
    }
}