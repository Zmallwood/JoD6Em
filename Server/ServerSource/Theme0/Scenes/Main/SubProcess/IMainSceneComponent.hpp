/*
 * IMainSceneComponent.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

class EngineInstance;

///
/// Base class for all components contained in MainScene.
///
class IMainSceneComponent {
    
  public:
    
    ///
    /// Optionally overridable for inheriting component classes.
    ///
    virtual void Update(UserID userID) {}
    
    ////
    /// 
    /// 
    /// @param userID 
    ///
    ///
    /// @param webSocket Web socket object associated with user.
    ///
    virtual void Render(UserID userID) const {}
};

}