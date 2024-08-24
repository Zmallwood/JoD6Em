/*
 * GUI.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUI.hpp"

namespace JoD {
GUI::GUI() : GUIComponent({0.0f, 0.0f}) {}

void GUI::Update(UserID userID) {
// Iterate through all components.
    for (auto& component : GetChildComponents())
// And update them.
        component->Update(userID);
}

void GUI::Render(UserID userID) {
// Iterate through all components.
    for (auto& component : GetChildComponents())
// And render them.
        component->Render(userID);
}
}
