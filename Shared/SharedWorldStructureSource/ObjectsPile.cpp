/*
 * ObjectsPile.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ObjectsPile.hpp"
#include "Object.hpp"

namespace JoD {
    struct ObjectsPile::Impl {
        
        std::vector<std::unique_ptr<Object>> m_objects;
    };
    
    ObjectsPile::ObjectsPile()
        : m_pImpl(std::make_unique<Impl>()){
        
    }
    
    ObjectsPile::~ObjectsPile() {
        
    }
    
    std::vector<Object*> ObjectsPile::GetObjects() const {
        
        std::vector<Object*> results;
        
        for (auto& entry : m_pImpl->m_objects) {
            
            results.push_back(entry.get());
        }
        
        return results;
    }
    
    void ObjectsPile::AddObject(std::string_view objectName) {
        
        m_pImpl->m_objects.push_back(std::make_unique<Object>(objectName));
    }
    
    bool ObjectsPile::HasObjects() const {
        
        return m_pImpl->m_objects.size() > 0;
    }
    
    
    void ObjectsPile::RemoveObject(Object* object) {
        
        for (auto i = 0; i < m_pImpl->m_objects.size(); i++) {
            
            auto &objectEntry = m_pImpl->m_objects.at(i);
            
            if (objectEntry.get() == object) {
                
                m_pImpl->m_objects.erase(m_pImpl->m_objects.begin() + i);
                return;
            }
        }
    }
    
    bool ObjectsPile::HasObjectOfType(std::string_view objectName) const {
        
        auto hashCode = Hash(objectName);
        
        for (auto& entry : m_pImpl->m_objects) {
            
            if (entry->GetType() == hashCode) {
                
                return true;
            }
        }
        
        return false;
    }
    
    void ObjectsPile::Clear() {
        
        m_pImpl->m_objects.clear();
    }
}