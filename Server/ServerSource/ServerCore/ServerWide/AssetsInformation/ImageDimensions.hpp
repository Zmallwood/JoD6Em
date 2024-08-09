/*
 * ImageDimensions.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Container storing all retrieved image dimensions from users.
    ///
    class ImageDimensions {
        
      public:
        void SetDimension(int imageNameHash, Size dimension);
        
        std::optional<Size> GetDimension(int imageNameHash) const;
        
        std::optional<Size> GetDimension(std::string_view imageName) const;
        
      private:
        std::map<int, Size> m_dimensions; ///< Stored image dimensions with image name hash code as key.
    };
}