/*
 * ClientEngine.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Engine for the client.
///
class ClientEngine {
    
  public:
    ///
    /// Run the client engine.
    ///
    void Run() const;
    
    ///
    /// Tells if the client engine is currently running.
    ///
    /// @return true If the game engine is running.
    /// @return false It the game engine is not running.
    ///
    bool GetRunning() const {
        
        return m_running;
    }
    
  private:
    
    // Members
    
    bool m_running {true};     ///< Engine is running as long as this is set to true.
};

}
