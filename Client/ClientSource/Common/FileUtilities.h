/*
 * FileUtilities.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    /// @brief Return file extensions for file with absolute path.
    /// @param abs_path Path to file.
    /// @return std::string File extension.
    std::string GetFileExtension(std::string_view abs_path);
    
    /// @brief Return file name without path or extension.
    /// @param abs_path Path to file.
    /// @return std::string Trimmed file name.
    std::string GetFilenameNoExtension(std::string_view abs_path);
}