/*
 * FileUtilities.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "FileUtilities.hpp"

namespace JoD {
    std::string GetFileExtension(std::string_view abs_path) {
        // Find last occurrence of '.' and keep the part following it.
        auto extension = abs_path.substr(abs_path.find_last_of('.') + 1);
        return extension.data();
    }
    
    std::string GetFilenameNoExtension(std::string_view abs_path) {
        // Find last occurence of '/' and get the part following it.
        auto name_with_ext =
            std::string(abs_path.substr(abs_path.find_last_of('/') + 1));
        // Then only keep the part preceeding the last occurrence of '.'.
        auto file_name = name_with_ext.substr(
            0,
            name_with_ext.find_last_of('.'));
        return file_name;
    }
}