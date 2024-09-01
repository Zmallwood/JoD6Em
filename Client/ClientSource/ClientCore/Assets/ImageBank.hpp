/*
 * ImageBank.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
#include "ImageEntry.hpp"

namespace JoD {

class ImageBank {
    
  public:
    ImageBank();
    ~ImageBank();
    std::optional<GLuint> GetImage(std::string_view imageName) const;
    std::optional<GLuint> GetImage(int imageNameHash) const;
    GLuint CreateBlankImage(std::string_view uniqueImageName);
    Size GetImageDimensions(int imageNameHash) const;
    
  private:
    void LoadImages();
    
    std::map<int, ImageEntry> m_images;
    const std::string k_relImagesPath{"Resources/Images"};
};
}
