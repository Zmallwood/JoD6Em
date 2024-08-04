/*
 * ImageBank.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    /// @brief Loads and provides image resources.
    class ImageBank {
    public:
        /// @brief Construct a new Image Bank object.
        ImageBank();
        
        /// @brief Destroy the image bank object.
        ~ImageBank();
        
        /// @brief Get the Image object.
        /// @param image_name of image, corresponding to filename wihtout extension.
        /// @return GLuint Resource ID of obtained image object.
        GLuint GetImage(std::string_view image_name) const;
        
        /// @brief Get the Image object.
        /// @param image_name_hash Hash code of image name, corresponding to hash code of filename
        ///                      wihtout extension.
        /// @return GLuint Resource ID of obtained image object.
        GLuint GetImage(int image_name_hash) const;
        
        /// @brief Create a blank image object.
        /// @param unique_image_name Name of newly created blank image.
        /// @return GLuint Resource ID of created image.
        GLuint CreateBlankImage(std::string_view unique_image_name);
        
    private:
        void LoadImages();
        
        std::map<int, GLuint> m_images; ///< Stores images by image name hash code.
        
        const std::string k_rel_images_path{"Resources/Images"}; ///< Path to images location.
    };
}