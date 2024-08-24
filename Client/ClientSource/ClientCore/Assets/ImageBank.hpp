/*
 * ImageBank.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "ImageEntry.hpp"

namespace JoD {
/// Loads and provides image resources.
class ImageBank {
  public:
/// Construct a new Image Bank object.
    ImageBank();
    
/// Destroy the image bank object.
    ~ImageBank();
    
/// Get the Image object.
/// @param imageName Of image, corresponding to filename wihtout extension.
/// @return std::optional<GLuint> Resource ID of obtained image object.
    std::optional<GLuint> GetImage(std::string_view imageName) const;
    
/// Get the Image object.
/// @param imageNameHash Hash code of image name, corresponding to hash code of filename
///                      wihtout extension.
/// @return std::optional<GLuint> Resource ID of obtained image object.
    std::optional<GLuint> GetImage(int imageNameHash) const;
    
/// Create a blank image object.
/// @param uniqueImageName Name of newly created blank image.
/// @return GLuint Resource ID of created image.
    GLuint CreateBlankImage(std::string_view uniqueImageName);
    
/// Get image dimensions for provided image name hash code.
/// @param imageNameHash Image name hash code to get dimensions for.
/// @return Size Image dimensions.
    Size GetImageDimensions(int imageNameHash) const;
    
  private:
// Loads all images from file system and storesboth the images and their dimensions.
    void LoadImages();
    
// Stores images as entries by image name hash code.
    std::map<int, ImageEntry> m_images;
// Path to images location.
    const std::string k_relImagesPath{"Resources/Images"};
};
}
