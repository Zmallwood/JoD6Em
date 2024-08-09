/*
 * TextMessages.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class TextMessages {
        
      public:
        void Print(std::string_view message);
        
        const std::vector<std::string>& Data() const {
            
            return m_data;
        }
        
      private:
        std::vector<std::string> m_data;
    };
}