// Copyright (c) 2024 Andreas Åkerberg.
#include "Assets.h"

namespace jod {
    namespace {
        GLuint LoadSingleImage(std::string_view absFilePath);
        SDL_Surface *LoadImageData(const char *filename);
    }
    ImageBank::ImageBank() {
        LoadImages(); // Load all images in images path.
    }
    ImageBank::~ImageBank() { // Iterate through all the loaded images.
        for (const auto &img : m_images) glDeleteTextures(1, &img.second); // Free every allocated image resource.
    }
    GLuint ImageBank::GetImage(std::string_view imageName) const {
        return GetImage(Hash(imageName)); // Hash the image name and call the function overload
    }
    GLuint ImageBank::GetImage(int imageNameHash) const {
        for (auto img : m_images) // Iterate through all the loaded images.
            // If its key, being the hash of the image name, equals
            // the hash of the specified name, then, return this image ID.
            if (img.first == imageNameHash) return img.second;
        return -1; // No image with the name found, return fail value.
    }
    GLuint ImageBank::CreateBlankImage(std::string_view uniqueImageName) {
        GLuint texID; // Generate new image resource
        glGenTextures(1, &texID); // and get its ID.
        // Insert new image entry with image name hash as key
        // and the new ID as value.
        m_images.insert({Hash(uniqueImageName), texID});
        return texID; // Return the ID of the newly created blank image resource.
    }
    void ImageBank::LoadImages() {
        using iterator = std::filesystem::recursive_directory_iterator;
        auto allImagesPath = k_relImagesPath + "/";
        for (auto &entry : iterator(allImagesPath)) {
            auto absPath = entry.path().string(); // Create path string to load the images from.
            if (FileExtension(absPath) != "png") continue; // Only handle files with png extenstion.
            auto texID = LoadSingleImage(absPath); // Load the current file as an image resource.
            auto imageName = FilenameNoExtension(absPath); // Extract its pure name without path or extension.
            // Insert a new entry into the images storage, with the
            // image name hash as key and the resource ID as value.
            m_images.insert({Hash(imageName), texID});
        }
    }
    namespace {
        GLuint LoadSingleImage(std::string_view absFilePath) {
            GLuint texID; // Declare variable to hold the resulting ID for the loaded image file.
            // Get image data from the image file.
            auto surf = LoadImageData(absFilePath.data());
            glEnable(GL_TEXTURE_2D); // We will work with 2D textures.
            glGenTextures(1, &texID); // Generate a new OpenGL texture and get its ID.
            glBindTexture(GL_TEXTURE_2D, texID); // Use the newly created OpenGL texture.
            // Apply necessary texture parameters.
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            // Transfer image data from SDL surface to OpenGL texture resource depending on
            // if the image format is RGB or RGBA (with or without alpha channel).
            if (surf->format->BytesPerPixel == 4)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA,
                             GL_UNSIGNED_BYTE, surf->pixels);
            else
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGB,
                             GL_UNSIGNED_BYTE, surf->pixels);
            // Free SDL surface resource, its not needed anymore as the image data is
            // stored in the OpenGL texture now.
            SDL_FreeSurface(surf);
            return texID; // Return the previously generated resource ID.
        }
        SDL_Surface *LoadImageData(const char *filename) {
            int width;
            int height;
            int bytesPerPixel;
            // Read data.
            void *data = stbi_load(filename, &width, &height, &bytesPerPixel, 0);
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
            auto surface = SDL_CreateRGBSurfaceFrom(data, width, height, bytesPerPixel * 8, pitch,
                                                    rMask, gMask, bMask, aMask);
            // If surface creation failed, then free image data and return nullptr.
            if (!surface) {
                stbi_image_free(data);
                return nullptr;
            }
            return surface; // Else if surface creation was successful, return the surface.
        }
    }
}
