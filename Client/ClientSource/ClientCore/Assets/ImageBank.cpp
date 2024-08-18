/*
 * ImageBank.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ImageBank.hpp"

namespace JoD {

namespace {

// Load single image from absolute file path.
ImageEntry LoadSingleImage(std::string_view absFilePath);

// Load pure image data from file name.
SDL_Surface *LoadImageData(const char *fileName);

}

ImageBank::ImageBank() {
    
// Load all images in images path.
    LoadImages();
}

ImageBank::~ImageBank() {
    
// Iterate through all the loaded images.
    for (const auto &image : m_images) {
        
// Free every allocated image resource.
        glDeleteTextures(1, &image.second.id);
    }
}

std::optional<GLuint> ImageBank::GetImage(std::string_view imageName) const {
    
// Hash the image name and call the function overload
    return GetImage(Hash(imageName));
}

std::optional<GLuint> ImageBank::GetImage(int imageNameHash) const {
    
// Iterate through all the loaded images.
    for (const auto &image : m_images) {
        
// If its key, being the hash of the image name, equals
// the hash of the specified name, then, return this image ID.
        if (image.first == imageNameHash) {
            
            return image.second.id;
        }
    }
    
// No image with the name found, return fail value.
    return -1;
}

GLuint ImageBank::CreateBlankImage(
    std::string_view uniqueImageName) {
    
// Generate new texture resource,
    GLuint texID;
    glGenTextures(1, &texID);
    
// Insert new image entry with image name hash as key
// and the new ID as value.
    m_images.insert({Hash(uniqueImageName), {texID, {0, 0}}});
    
// Return the ID of the newly created blank image resource.
    return texID;
}

Size ImageBank::GetImageDimensions(int imageNameHash) const {
    
// Try find the image with specified hash in the storage.
    if (m_images.contains(imageNameHash)) {
        
// And return its dimensions.
        return m_images.at(imageNameHash).dimensions;
    }
    
// If not found, return empty dimensions.
    return {0, 0};
}

void ImageBank::LoadImages() {
    
    using iterator = std::filesystem::recursive_directory_iterator;
    
    const auto allImagesPath = k_relImagesPath + "/";
    
    for (auto &entry : iterator(allImagesPath)) {
        
// Create path string to load the images from.
        const auto absPath = entry.path().string();
        
// Only handle files with png extenstion.
        if (GetFileExtension(absPath) != "png") {
            
            continue;
        }
        
// Load the current file as an image resource.
        const auto imageEntry = LoadSingleImage(absPath);
        
// Extract its pure name without path or extension.
        const auto imageName = GetFilenameNoExtension(absPath);
        
// Insert a new entry into the images storage, with the
// image name hash as key and the resource ID as value.
        m_images.insert({Hash(imageName), imageEntry});
    }
}

namespace {

ImageEntry LoadSingleImage(std::string_view absFilePath) {
    
// Declare variable to hold the resulting ID for the loaded image file.
    GLuint texID;
    
// Get image data from the image file.
    const auto surface = LoadImageData(absFilePath.data());
    
// We will work with 2D textures.
    glEnable(GL_TEXTURE_2D);
    
// Generate a new OpenGL texture and get its ID.
    glGenTextures(1, &texID);
    
// Use the newly created OpenGL texture.
    glBindTexture(GL_TEXTURE_2D, texID);
    
// Apply necessary texture parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
// Transfer image data from SDL surface to OpenGL texture resource depending on
// if the image format is RGB or RGBA (with or without alpha channel).
    if (surface->format->BytesPerPixel == 4) {
        
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    }
    else {
        
        glTexImage2D(
            GL_TEXTURE_2D, 0,  GL_RGBA, surface->w, surface->h, 0,
            GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
    }
    
    const auto dimensions = Size {surface->w, surface->h};
    
// Free SDL surface resource, its not needed anymore as the image data is
// stored in the OpenGL texture now.
    SDL_FreeSurface(surface);
    
// Return the previously generated resource ID.
    return {texID, dimensions};
}

SDL_Surface *LoadImageData(const char *fileName) {
    
    int width;
    int height;
    int bytesPerPixel;
    
// Read data.
    void *data = stbi_load(
        fileName, &width, &height, &bytesPerPixel, 0);
    
// Calculate pitch.
    int pitch;
    pitch = width * bytesPerPixel;
    pitch = (pitch + 3) & ~3;
    
// Setup relevance bitmask.
    int rMask;
    int gMask;
    int bMask;
    int aMask;
    
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
    rMask = 0x000000FF;
    gMask = 0x0000FF00;
    bMask = 0x00FF0000;
    aMask = (bytesPerPixel == 4) ? 0xFF000000 : 0;
#else
    int s = (bytesPerPixel == 4) ? 0 : 8;
    rMask = 0xFF000000 >> s;
    gMask = 0x00FF0000 >> s;
    bMask = 0x0000FF00 >> s;
    aMask = 0x000000FF >> s;
#endif
    
// Create SDL surface from image data.
    const auto surface = SDL_CreateRGBSurfaceFrom(
        data, width, height,
        bytesPerPixel * 8, pitch, rMask, gMask, bMask, aMask);
    
// If surface creation failed, then free image data and return nullptr.
    if (!surface) {
        
        stbi_image_free(data);
        
        return nullptr;
    }
    
// Else if surface creation was successful, return the surface.
    return surface;
}

}

}
