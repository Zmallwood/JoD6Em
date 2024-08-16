/*
 * GUI.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "GUIComponent.hpp"

namespace JoD {

    class GUI {
      public:
        void Update(UserID userID);

        void Render(UserID userID) const;

        template<class T, class ... Args>
        std::shared_ptr<T> AddComponent(Args... args) {

            auto newComponent = std::make_shared<T>(args ...);

            m_components.push_back(newComponent);

            return newComponent;
        }

      private:

        // Members

        std::vector<std::shared_ptr<GUIComponent>> m_components;
    };
}
