/*
 * TextMessages.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    ///
    /// Holds a storage of all messages that has been printed.
    /// Used by GUITextConsole to show them to the user in the GUI.
    ///
    class TextMessages {
        
      public:
        
        ///
        /// Add new message to the TextMessages storage.
        /// 
        /// @param message Message to add.
        ///
        void Print(std::string_view message);
        
        ///
        /// Get collection with all the printed messages.
        /// 
        /// @return const std::vector<std::string>& Collection of printed messages.
        ///
        const std::vector<std::string>& GetData() const {
            
            return m_data;
        }
        
      private:
        
        // Members
        
        std::vector<std::string> m_data; ///< Storage of all the printed messages.
    };
}
