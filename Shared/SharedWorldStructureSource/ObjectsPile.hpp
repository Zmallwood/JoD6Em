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
        
        void AddObject(std::unique_ptr<Object> object);
        
        std::vector<Object*> GetObjects() const;
        
        bool HasObjects() const;
        
        void RemoveObject(Object* object);
        
        bool HasObjectOfType(std::string_view objectName) const;
        
        void Clear();
        
      private:
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
    };
}