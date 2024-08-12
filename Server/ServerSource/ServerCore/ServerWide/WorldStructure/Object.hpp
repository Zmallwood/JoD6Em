/*
 * Object.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ObjectMaturity.hpp"

namespace JoD {
    
    ///
    /// Represents an object in the game world.
    ///
    class Object {
        
      public:
        ///
        /// Construct a new Object object of specified type.
        ///
        /// @param objectName Name of type of object o create.
        ///
        Object(std::string_view objectName);
        
        ///
        /// Get the hash code of the type of the object.
        ///
        /// @return int Hash code of name of type.
        ///
        int GetType() const {
            
            return m_type;
        }
        
        ///
        /// Get the timepoint for when the object was created.
        /// 
        /// @return TimePoint Point in time when this object was created.
        ///
        TimePoint GetCreationTime() const {
            
            return m_creationTime;
        }
        
        ///
        /// Get the durability of the object where 1.0f is full
        /// durability, and 0.0f is out of durability.
        /// 
        /// @return float Durability of the object.
        ///
        float GetDurability() const {
            
            return m_durability;
        }
        
        ///
        /// Set the durability object where 1.0f is full
        /// durability, and 0.0f is out of durability.
        /// 
        /// @param durability New durability of the object.
        ///
        void SetDurability(float durability) {
            
            m_durability = durability;
        }
        
      private:
        float m_durability {1.0f}; ///< Durability of the object in the range 0.0f-1.0f.
        int m_type {0}; ///< Hash code of name of object type.
        TimePoint m_creationTime; ///< Point in time when the object was created, is set in the ctor.
        ObjectMaturity m_maturity {ObjectMaturity::Mature}; ///< Maturity stage of the object.
    };
}