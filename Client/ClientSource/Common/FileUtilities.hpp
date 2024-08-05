/*
 * FileUtilities.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    ///
    /// Return file extensions for file with absolute path.
    ///
    /// @param absPath Path to file.
    /// @return std::string File extension.
    ///
    std::string GetFileExtension(std::string_view absPath);
    
    ///
    /// Return file name without path or extension.
    ///
    /// @param absPath Path to file.
    /// @return std::string Trimmed file name.
    ///
    std::string GetFilenameNoExtension(std::string_view absPath);
}