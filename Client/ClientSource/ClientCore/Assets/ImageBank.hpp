/*
 * ImageBank.hpp
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
        /// @param imageName of image, corresponding to filename wihtout extension.
        /// @return GLuint Resource ID of obtained image object.
        GLuint GetImage(std::string_view imageName) const;
        
        /// @brief Get the Image object.
        /// @param imageNameHash Hash code of image name, corresponding to hash code of filename
        ///                      wihtout extension.
        /// @return GLuint Resource ID of obtained image object.
        GLuint GetImage(int imageNameHash) const;
        
        /// @brief Create a blank image object.
        /// @param uniqueImageName Name of newly created blank image.
        /// @return GLuint Resource ID of created image.
        GLuint CreateBlankImage(std::string_view uniqueImageName);
        
      private:
        void LoadImages();
        
        std::map<int, GLuint> m_images; ///< Stores images by image name hash code.
        
        const std::string k_relImagesPath{"Resources/Images"}; ///< Path to images location.
    };
}