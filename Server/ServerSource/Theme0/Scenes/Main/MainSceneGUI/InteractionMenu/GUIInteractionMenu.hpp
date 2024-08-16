/*
 * GUIInteractionMenu.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/GUICore/GUIComponent.hpp"
#include "MenuEntry.hpp"

namespace JoD {

    class GUIInteractionMenu : public GUIComponent {

      public:
        GUIInteractionMenu();

        void UpdateDerived(UserID userID) override;

        void RenderDerived(UserID userID) const override;

      private:
        BoxF GetBounds() const;

        // Members

        SizeF m_size {0.1f, 0.05f};

        bool m_active {false};

        std::vector<MenuEntry> m_menuEntries;

        Point m_clickedCoord = {-1, -1};

        const float k_menuRowHeight {0.1f};
    };
}
