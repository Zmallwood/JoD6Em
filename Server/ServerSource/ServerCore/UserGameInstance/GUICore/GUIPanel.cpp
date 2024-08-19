/*
 * GUIPanel.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "GUIPanel.hpp"
#include "ServerCore/Net/InstructionsSending.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {

GUIPanel::GUIPanel(BoxF bounds)
    : GUIComponent(bounds.GetPosition()), m_size(bounds.GetSize()) {}

void GUIPanel::RenderDerived(UserID userID) const {
    
// Draw the background image.
    UserSendDrawImageRepeated(
        userID, "GUIPanelBground", GetInnerBounds(userID),
        {m_size.w, m_size.w*m_size.h/m_size.w});
    
    auto boundsLeftBorder = BoxF {GetOuterBounds().x,
                                  GetOuterBounds().y + m_borderWidth * _<EngineGet>().GetAspectRatio(userID).value(),
                                  m_borderWidth,
                                  GetOuterBounds().h - 2*m_borderWidth * _<EngineGet>().GetAspectRatio(userID).value()};
    
    UserSendDrawImageRepeated(
        userID, "GUIBorderVertical", boundsLeftBorder,
        {1.0f, boundsLeftBorder.h/boundsLeftBorder.w});
    
    auto boundsRightBorder = BoxF {GetOuterBounds().x + GetOuterBounds().w -
                                   m_borderWidth,
                                   GetOuterBounds().y + m_borderWidth * _<EngineGet>().GetAspectRatio(userID).value(),
                                   m_borderWidth,
                                   GetOuterBounds().h - 2*m_borderWidth * _<EngineGet>().GetAspectRatio(userID).value()};
    
    UserSendDrawImageRepeated(
        userID, "GUIBorderVertical", boundsRightBorder,
        {1.0f, boundsRightBorder.h/boundsRightBorder.w});
    
    auto boundsTopBorder = BoxF {GetOuterBounds().x + m_borderWidth,
                                 GetOuterBounds().y,
                                 GetOuterBounds().w - 2*m_borderWidth,
                                 m_borderWidth * _<EngineGet>().GetAspectRatio(
                                     userID).value()};
    
    UserSendDrawImageRepeated(
        userID, "GUIBorderHorizontal", boundsTopBorder,
        {boundsTopBorder.w/boundsTopBorder.h, 1.0f});
    
    auto boundsBottomBorder = BoxF {GetOuterBounds().x + m_borderWidth,
                                    GetOuterBounds().y + GetOuterBounds().h -
                                    m_borderWidth*
                                    _<EngineGet>().GetAspectRatio(
                                        userID).value(),
                                    GetOuterBounds().w - 2*m_borderWidth,
                                    m_borderWidth * _<EngineGet>().
                                    GetAspectRatio(userID).value()};
    
    UserSendDrawImageRepeated(
        userID, "GUIBorderHorizontal", boundsBottomBorder,
        {boundsBottomBorder.w/boundsBottomBorder.h, 1.0f});
    
    
    auto boundsTopLeftCorner = BoxF {GetOuterBounds().x,
                                     GetOuterBounds().y,
                                     m_borderWidth,
                                     m_borderWidth * _<EngineGet>().
                                     GetAspectRatio(userID).value()};
    
    UserSendDrawImage(
        userID, "GUIBorderTopLeft", boundsTopLeftCorner);
    
    
    auto boundsTopRightCorner = BoxF {GetOuterBounds().x + GetOuterBounds().w -
                                      m_borderWidth,
                                      GetOuterBounds().y,
                                      m_borderWidth,
                                      m_borderWidth * _<EngineGet>().
                                      GetAspectRatio(userID).value()};
    UserSendDrawImage(
        userID, "GUIBorderTopRight", boundsTopRightCorner);
    
    
    auto boundsBottomLeftCorner = BoxF {GetOuterBounds().x,
                                        GetOuterBounds().y +
                                        GetOuterBounds().h - m_borderWidth* _<EngineGet>().
                                        GetAspectRatio(userID).value(),
                                        m_borderWidth,
                                        m_borderWidth * _<EngineGet>().
                                        GetAspectRatio(userID).value()};
    UserSendDrawImage(
        userID, "GUIBorderBottomLeft", boundsBottomLeftCorner);
    
    
    auto boundsBottomRightCorner = BoxF {GetOuterBounds().x +
                                         GetOuterBounds().w - m_borderWidth,
                                         GetOuterBounds().y+
                                         GetOuterBounds().h - m_borderWidth* _<EngineGet>().
                                         GetAspectRatio(userID).value(),
                                         m_borderWidth,
                                         m_borderWidth * _<EngineGet>().
                                         GetAspectRatio(userID).value()};
    UserSendDrawImage(
        userID, "GUIBorderBottomRight", boundsBottomRightCorner);
}

BoxF GUIPanel::GetInnerBounds(UserID userID) const {
    
// Combine position and size to create bounds.
    return {m_position.x + m_borderWidth,
            m_position.y + m_borderWidth *
            _<EngineGet>().GetAspectRatio(userID).value(),
            m_size.w - 2*m_borderWidth,
            m_size.h - 2*m_borderWidth *
            _<EngineGet>().GetAspectRatio(userID).value()};
}

BoxF GUIPanel::GetOuterBounds() const {
    
    return {m_position.x, m_position.y,
            m_size.w, m_size.h};
}

}