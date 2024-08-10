/*
 * Object.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class Object {
        
      public:
        Object(std::string_view objectName);
        
        int GetType() const {
            
            return m_type;
        }
        
      private:
        int m_type {0};
    };
}