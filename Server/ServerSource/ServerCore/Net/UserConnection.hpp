/*
 * UserConnection.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"

namespace JoD {
    
    class UserGameInstanceEngine;
    
    ///
    /// Created for each user that connects to the web socket server.
    ///
    class UserConnection {
        
      public:
        ///
        /// Starts a web socket loop thread for the user.
        ///
        /// @param socket Socket object obtained from web
        ///               socket server and associated with the user.
        ///
        UserConnection(Socket socket);
        
        ///
        /// Send an image drawing instruction to the user.
        ///
        /// @param webSocket Socket object.
        /// @param imageName Name of image to draw.
        /// @param destination Destination to draw the image at.
        ///
        void SendImageDrawInstruction(
            WebSocket &webSocket,
            std::string_view imageName,
            BoxF destination) const;
        
        ///
        /// Send an image drawing instruction to the user.
        ///
        /// @param webSocket Socket object.
        /// @param imageNamehash Hash code of image name to draw.
        /// @param destination Destination to draw the image at.
        ///
        void SendImageDrawInstruction(
            WebSocket &webSocket,
            int imageNamehash,
            BoxF destination) const;
        
        ///
        /// Send a text drawing instruction to the user.
        ///
        /// @param webSocket Socket object.
        /// @param text Text to draw.
        /// @param position Position to draw the text at.
        ///
        void SendTextDrawInstruction(
            WebSocket &webSocket,
            std::string_view text, PointF position) const;
        
        ///
        /// Send instruction to present canvas to the user.
        ///
        /// @param webSocket Socket object.
        ///
        void SendPresentCanvasInstruction(WebSocket &webSocket) const;
        
        ///
        /// Send request to user to retrieve dimensions for an image.
        ///
        /// @param webSocket Socket object.
        /// @param imageNameHash Hash code of image name to get dimensions for.
        ///
        void SendRequestImageDimensions(
            WebSocket &webSocket,
            int imageNameHash) const;
        
        std::unique_ptr<UserGameInstanceEngine>
        m_userGameInstanceEngine; ///< Engine running for this specific user.
        
      private:
        ///
        /// Running game loop for user.
        ///
        /// @param socket Socket object.
        ///
        void DoSession(Socket socket);
        
        ///
        /// Running loop for reading incoming web socket messages and handle them.
        /// 
        /// @param webSocket Socket object.
        ///
        void DoSessionNested(WebSocket* webSocket);
    };
}