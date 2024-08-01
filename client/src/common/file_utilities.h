// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod {
    //! \brief Return file extensions for file with absolute path.
    //! \param absPath Path to file.
    //! \return std::string File extension.
    std::string file_extension(std::string_view absPath);
    
    //! \brief Return file name without path or extension.
    //! \param absPath Path to file.
    //! \return std::string Trimmed file name.
    std::string filename_no_extension(std::string_view absPath);
}