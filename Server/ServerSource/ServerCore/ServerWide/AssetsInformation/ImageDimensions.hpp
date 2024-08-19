/*
 * ImageDimensions.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Container storing all retrieved image dimensions from users.
///
class ImageDimensions {
    
  public:
    ///
    /// Store the dimensions for an image.
    ///
    /// @param imageNameHash Hash code of image to store dimension for.
    /// @param dimension The dimension value.
    ///
    void SetDimension(int imageNameHash, Size dimension);
    
    ///
    /// Get the dimensions for an image.
    ///
    /// @param imageNameHash Hash code of image name to get dimensions for.
    /// @return std::optional<Size> An optional object with the dimensions value, or std::nullopt
    ///         if no stored dimension with the specified imageNameHash was found.
    ///
    std::optional<Size> GetDimension(int imageNameHash) const;
    
    ///
    /// Get the dimensions for an image.
    ///
    /// @param imageName Name of image to get dimensions for.
    /// @return std::optional<Size> An optional object with the dimensions value, or std::nullopt
    ///         if no stored dimension with the specified imageName was found.
    ///
    std::optional<Size> GetDimension(std::string_view imageName) const;
    
  private:
    
    // Members
    
    std::map<int, Size> m_dimensions;     ///< Stored image dimensions with image name hash code as key.
};

}
