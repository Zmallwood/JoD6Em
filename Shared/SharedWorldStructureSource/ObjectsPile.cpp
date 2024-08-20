/*
 * ObjectsPile.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ObjectsPile.hpp"
#include "Object.hpp"

namespace JoD {

struct ObjectsPile::Impl {
    
    std::vector<std::shared_ptr<Object>> m_objects;
};

ObjectsPile::ObjectsPile()
    : m_pImpl(std::make_unique<Impl>()) {}

ObjectsPile::~ObjectsPile() {}

std::vector<std::shared_ptr<Object>> ObjectsPile::GetObjects() const {
    
    std::vector<std::shared_ptr<Object>> results;
    
    for (auto& entry : m_pImpl->m_objects) {
        
        results.push_back(entry);
    }
    
    return results;
}

void ObjectsPile::AddObject(std::string_view objectName, int quantity) {
    
    m_pImpl->m_objects.push_back(
        std::make_unique<Object>(
            objectName,
            quantity));
}


void ObjectsPile::AddObject(std::shared_ptr<Object> object) {
    
    m_pImpl->m_objects.push_back(object);
}

bool ObjectsPile::HasObjects() const {
    
    return m_pImpl->m_objects.size() > 0;
}


void ObjectsPile::RemoveObject(std::shared_ptr<Object> object) {
    
    for (auto i = 0; i < m_pImpl->m_objects.size(); i++) {
        
        auto &objectEntry = m_pImpl->m_objects.at(i);
        
        if (objectEntry == object) {
            
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

int ObjectsPile::GetNumObjects() const {
    return m_pImpl->m_objects.size();
}

}