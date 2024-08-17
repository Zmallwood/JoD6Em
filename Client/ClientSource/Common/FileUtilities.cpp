/*
 * FileUtilities.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "FileUtilities.hpp"

namespace JoD {

std::string GetFileExtension(std::string_view absPath) {
    
    // Find last occurrence of '.' and keep the part following it.
    const auto extension = absPath.substr(absPath.find_last_of('.') + 1);
    
    return extension.data();
}

std::string GetFilenameNoExtension(std::string_view absPath) {
    
    // Find last occurence of '/' and get the part following it.
    const auto nameWithExt =
        std::string(absPath.substr(absPath.find_last_of('/') + 1));
    
    // Then only keep the part preceeding the last occurrence of '.'.
    const auto fileName = nameWithExt.substr(
        0, nameWithExt.find_last_of('.'));
    
    return fileName;
}

}