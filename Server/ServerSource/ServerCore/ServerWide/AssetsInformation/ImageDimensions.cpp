/*
 * ImageDimensions.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ImageDimensions.hpp"

namespace JoD {
    
    void ImageDimensions::SetDimension(int imageNameHash, Size dimension) {
        
        m_dimensions[imageNameHash] = dimension;
    }
    
    
    std::optional<Size> ImageDimensions::GetDimension(int imageNameHash) const {
        
        if (m_dimensions.contains(imageNameHash)) {
            
            return m_dimensions.at(imageNameHash);
        }
        
        return std::nullopt; 
    }
    
    std::optional<Size> ImageDimensions::GetDimension(std::string_view imageName) const {
        
        return GetDimension(Hash(imageName));
    }
}