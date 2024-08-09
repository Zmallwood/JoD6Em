/*
 * EngineInstancesManager.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    class EngineInstance;
    
    class EngineInstancesManager {
      public:
        UserID RegisterEngineInstance(EngineInstance& engineInstance);
                                    
        EngineInstance* GetInstance(UserID userID) const;
        
      private:
        std::map<UserID, EngineInstance*> m_engineInstances;
        inline static UserID s_currentUserID {0};
    };
}