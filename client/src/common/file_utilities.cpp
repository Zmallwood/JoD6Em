// file_utilities.cpp
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
//

#include "file_utilities.h"

namespace jod {
    std::string
    file_extension(std::string_view absPath){
        // Find last occurrence of '.' and keep the part following it.
        auto extension = absPath.substr(absPath.find_last_of('.') + 1);
        return extension.data();
    }
    
    std::string
    filename_no_extension(std::string_view absPath){
        // Find last occurence of '/' and get the part following it.
        auto nameWithExt =
            std::string(absPath.substr(absPath.find_last_of('/') + 1));
        // Then only keep the part preceeding the last occurrence of '.'.
        auto fileName = nameWithExt.substr(0, nameWithExt.find_last_of('.'));
        return fileName;
    }
}