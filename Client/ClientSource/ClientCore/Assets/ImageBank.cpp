/*
 * ImageBank.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ImageBank.h"

namespace jod {
    namespace {
        // Load single image from absolute file path.
        GLuint load_single_image(std::string_view abs_file_path);
        // Load pure image data from file name.
        SDL_Surface *load_image_data(const char *file_name);
    }
    
    image_bank::image_bank() {
        load_images(); // Load all images in images path.
    }
    
    image_bank::~image_bank() { // Iterate through all the loaded images.
        for (const auto &image : m_images)
            glDeleteTextures(1, &image.second); // Free every allocated image resource.
    }
    
    GLuint image_bank::get_image(std::string_view image_name) const {
        return get_image(jod::hash(image_name)); // Hash the image name and call the function overload
    }
    
    GLuint image_bank::get_image(int image_name_hash) const {
        for (auto image : m_images) // Iterate through all the loaded images.
            // If its key, being the hash of the image name, equals
            // the hash of the specified name, then, return this image ID.
            if (image.first == image_name_hash) return image.second;
        return -1; // No image with the name found, return fail value.
    }
    
    GLuint image_bank::create_blank_image(
        std::string_view unique_image_name) {
        GLuint tex_id; // Generate new image resource,
        glGenTextures(1, &tex_id); // and get its ID.
        // Insert new image entry with image name hash as key
        // and the new ID as value.
        m_images.insert({jod::hash(unique_image_name), tex_id});
        return tex_id; // Return the ID of the newly created blank image resource.
    }
    
    void image_bank::load_images() {
        using iterator = std::filesystem::recursive_directory_iterator;
        auto all_images_path = k_rel_images_path + "/";
        for (auto &entry : iterator(all_images_path)) {
            auto abs_path = entry.path().string(); // Create path string to load the images from.
            if (file_extension(abs_path) != "png") continue; // Only handle files with png extenstion.
            auto tex_id = load_single_image(abs_path); // Load the current file as an image resource.
            auto image_name = filename_no_extension(
                abs_path); // Extract its pure name without path or extension.
            // Insert a new entry into the images storage, with the
            // image name hash as key and the resource ID as value.
            m_images.insert({jod::hash(image_name), tex_id});
        }
    }
    
    namespace {
        GLuint load_single_image(std::string_view abs_file_path) {
            GLuint tex_id; // Declare variable to hold the resulting ID for the loaded image file.
            // Get image data from the image file.
            auto surface = load_image_data(abs_file_path.data());
            glEnable(GL_TEXTURE_2D); // We will work with 2D textures.
            glGenTextures(1, &tex_id); // Generate a new OpenGL texture and get its ID.
            glBindTexture(GL_TEXTURE_2D, tex_id); // Use the newly created OpenGL texture.
            // Apply necessary texture parameters.
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            // Transfer image data from SDL surface to OpenGL texture resource depending on
            // if the image format is RGB or RGBA (with or without alpha channel).
            if (surface->format->BytesPerPixel == 4)
                glTexImage2D(
                    GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
                    GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
            else
                glTexImage2D(
                    GL_TEXTURE_2D, 0,  GL_RGBA, surface->w, surface->h, 0,
                    GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
            // Free SDL surface resource, its not needed anymore as the image data is
            // stored in the OpenGL texture now.
            SDL_FreeSurface(surface);
            return tex_id; // Return the previously generated resource ID.
        }
        
        SDL_Surface *load_image_data(const char *file_name) {
            int width;
            int height;
            int bytes_per_pixel;
            // Read data.
            void *data = stbi_load(
                file_name, &width, &height, &bytes_per_pixel,
                0);
            // Calculate pitch.
            int pitch;
            pitch = width * bytes_per_pixel;
            pitch = (pitch + 3) & ~3;
            // Setup relevance bitmask.
            int r_mask;
            int g_mask;
            int b_mask;
            int a_mask;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
            r_mask = 0x000000FF;
            g_mask = 0x0000FF00;
            b_mask = 0x00FF0000;
            a_mask = (bytes_per_pixel == 4) ? 0xFF000000 : 0;
#else
            int s = (bytesPerPixel == 4) ? 0 : 8;
            rMask = 0xFF000000 >> s;
            gMask = 0x00FF0000 >> s;
            bMask = 0x0000FF00 >> s;
            aMask = 0x000000FF >> s;
#endif
            // Create SDL surface from image data.
            auto surface = SDL_CreateRGBSurfaceFrom(
                data, width, height,
                bytes_per_pixel * 8, pitch, r_mask, g_mask, b_mask, a_mask);
            // If surface creation failed, then free image data and return nullptr.
            if (!surface) {
                stbi_image_free(data);
                return nullptr;
            }
            return surface; // Else if surface creation was successful, return the surface.
        }
    }
}
