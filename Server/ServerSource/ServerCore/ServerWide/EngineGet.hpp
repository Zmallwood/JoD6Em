/*
 * EngineInstancesManager.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class EngineInstance;
    class Player;
    class SceneManager;
    class MouseInput;
    class TextMessages;
    
    class EngineGet {
      public:
        EngineGet();
        
        ~EngineGet();
        
        UserID RegisterEngineInstance(Socket socket);
        
        EngineInstance* GetInstance(UserID userID) const;
        
        std::optional<PointF> GetMousePosition(UserID userID) const;
        
        std::optional<float> GetAspectRatio(UserID userID) const;
        
        Player* GetPlayer(UserID userID) const;
        
        SceneManager* GetSceneManager(UserID userID) const;
        
        MouseInput* GetMouseInput(UserID userID) const;
        
        TextMessages* GetTextMessages(UserID userID) const;
        
        WebSocket *GetWebSocket(UserID userID) const;
                
      private:
        struct Impl;
        
        std::unique_ptr<Impl> m_pImpl;
        
        inline static UserID s_currentUserID {1}; ///< Note: IDs start at 1 so 0 can be used for unspecified/lacking IDs.
    };
}