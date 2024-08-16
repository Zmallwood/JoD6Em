/*
 * ObjectsPile.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class Object;
    
    class ObjectsPile {
        
      public:
      
        ObjectsPile();
        
        ~ObjectsPile();
        
        void AddObject(std::string_view objectName);
        
        void AddObject(std::shared_ptr<Object> object);
        
        std::vector<std::shared_ptr<Object>> GetObjects() const;
        
        bool HasObjects() const;
        
        void RemoveObject(std::shared_ptr<Object> object);
        
        bool HasObjectOfType(std::string_view objectName) const;
        
        void Clear();
        
      private:
      
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}