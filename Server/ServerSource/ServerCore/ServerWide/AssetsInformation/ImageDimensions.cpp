/*
 * ImageDimensions.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ImageDimensions.hpp"

namespace JoD {
void ImageDimensions::SetDimension(int imageNameHash, Size dimension) {
// Store dimension in storage.
    m_dimensions[imageNameHash] = dimension;
}

std::optional<Size> ImageDimensions::GetDimension(int imageNameHash) const {
// Check if dimension with provided hash code exists.
    if (m_dimensions.contains(imageNameHash))
// If so, return it.
        return m_dimensions.at(imageNameHash);
// No dimension found, return empty value.
    return std::nullopt;
}

std::optional<Size> ImageDimensions::GetDimension(
    std::string_view imageName) const {
// Forward function call to overload.
    return GetDimension(Hash(imageName));
}
}