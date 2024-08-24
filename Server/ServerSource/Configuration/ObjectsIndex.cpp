/*
 * ObjectsIndex.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ObjectsIndex.hpp"
#include "ObjectFlags.hpp"

namespace JoD {
ObjectsIndex::ObjectsIndex() {
// Insert object flags for certain objects.
    m_objectFlags.insert(
        {Hash("ObjectPinkFlower"),
         {.name="Pink flower", .flags = ObjectFlags::k_walkThrough}});
    m_objectFlags.insert(
        {Hash("ObjectPoolOfBlood"),
         {.name="Pool of blood", .flags = ObjectFlags::k_walkThrough}});
    m_objectFlags.insert(
        {Hash("ObjectBoneRemains"),
         {.name="Bone remains", .flags = ObjectFlags::k_walkThrough}});
    m_objectFlags.insert(
        {Hash("ObjectGrass"),
         {.name="Grass",
                           .flags = ObjectFlags::k_walkThrough}});
    m_objectFlags.insert(
        {Hash("ObjectFelledTree"),
         {.name="Felled tree", .flags = ObjectFlags::k_walkThrough}});
    m_objectFlags.insert(
        {Hash("ObjectTree1"),
         {.name="Tree type 1", .flags = 0}});
    m_objectFlags.insert(
        {Hash("ObjectTree2"),
         {.name="Tree type 2", .flags = 0}});
    m_objectFlags.insert(
        {Hash("ObjectWoodLog"),
         {.name="Wood log", .flags = ObjectFlags::k_walkThrough}});
    m_objectFlags.insert(
        {Hash("ObjectWoodPlank"),
         {.name="Wood plank", .flags = ObjectFlags::k_walkThrough}});
}

bool ObjectsIndex::CanWalkThroughObject(int objectNameHash) const {
// Check if object type exists in storage.
    if (m_objectFlags.contains(objectNameHash)) {
// If it does, return wether it has the walk-through flag or not.
        return (m_objectFlags.at(objectNameHash).flags &
                ObjectFlags::k_walkThrough) != 0;
    }
// Return false as default, if the object type doesnt exist in storage.
    return false;
}

std::string ObjectsIndex::GetObjectName(int objectNameHash) const {
    if (m_objectFlags.contains(objectNameHash)) {
        return m_objectFlags.at(objectNameHash).name;
    }
    return "Unnamed object";
}
}
