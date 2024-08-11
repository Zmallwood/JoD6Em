/*
 * Object.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ObjectMaturity.hpp"

namespace JoD {
    
    class Object {
        
      public:
        Object(std::string_view objectName);
        
        int GetType() const {
            
            return m_type;
        }
        
        TimePoint GetCreationTime() const {
            
            return m_creationTime;
        }

        float m_durability {1.0f};
        
      private:
        int m_type {0};
        TimePoint m_creationTime;
        ObjectMaturity m_maturity {ObjectMaturity::Mature};
    };
}