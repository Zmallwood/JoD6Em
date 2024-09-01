/*
 * ImageBank.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ImageBank.hpp"

namespace JoD {

namespace {
    
    ImageEntry LoadSingleImage(std::string_view absFilePath);
    SDL_Surface *LoadImageData(const char *fileName);
}

ImageBank::ImageBank() {
    
    LoadImages();
}

ImageBank::~ImageBank() {
    
    for (auto &image : m_images)
        glDeleteTextures(1, &image.second.id);
}

std::optional<GLuint> ImageBank::GetImage(
    std::string_view imageName) const {
    
    return GetImage(Hash(imageName));
}

std::optional<GLuint> ImageBank::GetImage(
    int imageNameHash) const {
    
    for (auto &image : m_images)
        if (image.first == imageNameHash)
            return image.second.id;
    
    return std::nullopt;
}

GLuint ImageBank::CreateBlankImage(
    std::string_view uniqueImageName) {
    
    GLuint texID;
    glGenTextures(1, &texID);
    
    m_images.insert({Hash(uniqueImageName), {texID, {0, 0}}});
    
    return texID;
}

Size ImageBank::GetImageDimensions(int imageNameHash) const {
    
    if (m_images.contains(imageNameHash))
        return m_images.at(imageNameHash).dimensions;
    
    return {0, 0};
}

void ImageBank::LoadImages() {
    
    using iterator = std::filesystem::recursive_directory_iterator;
    
    auto allImagesPath = k_relImagesPath + "/";
    
    for (auto &entry : iterator(allImagesPath)) {
        
        auto absPath = entry.path().string();
        
        if (GetFileExtension(absPath) != "png") continue;
        
        auto imageEntry = LoadSingleImage(absPath);
        auto imageName = GetFilenameNoExtension(absPath);
        
        m_images.insert({Hash(imageName), imageEntry});
    }
}

namespace {
    
    ImageEntry LoadSingleImage(std::string_view absFilePath) {
        
        GLuint texID;
        
        auto surface = LoadImageData(absFilePath.data());
        
        glEnable(GL_TEXTURE_2D);
        
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
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
        
        auto dimensions = Size {surface->w, surface->h};
        
        SDL_FreeSurface(surface);
        
        return {texID, dimensions};
    }
    
    SDL_Surface *LoadImageData(const char *fileName) {
        
        int width;
        int height;
        int bytesPerPixel;
        
        void *data = stbi_load(
            fileName, &width, &height, &bytesPerPixel, 0);
        
        int pitch;
        pitch = width * bytesPerPixel;
        pitch = (pitch + 3) & ~3;
        
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
        
        auto surface = SDL_CreateRGBSurfaceFrom(
            data, width, height,
            bytesPerPixel * 8, pitch, rMask, gMask, bMask, aMask);
        
        if (!surface) {
            
            stbi_image_free(data);
            
            return nullptr;
        }
        
        return surface;
    }
}
}
