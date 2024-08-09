/*
 * InstructionsSending.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "InstructionsSending.hpp"
#include "MessageCodes.hpp"

namespace JoD {
    
    void SendImageDrawInstruction(
        WebSocket &webSocket,
        std::string_view
        imageName,
        BoxF destination) {
        
        SendImageDrawInstruction(webSocket, Hash(imageName), destination);
    }
    
    void SendImageDrawInstruction(
        WebSocket &webSocket,
        int imageNameHash,
        BoxF destination) {
        
        const auto messageCode = MessageCodes::k_drawImageInstr;
        
        const auto x = (int)(destination.x * NetConstants::k_floatPrecision);
        const auto y = (int)(destination.y * NetConstants::k_floatPrecision);
        const auto w = (int)(destination.w * NetConstants::k_floatPrecision);
        const auto h = (int)(destination.h * NetConstants::k_floatPrecision);
        
        auto data = std::vector<int>();
        
        data.push_back(messageCode);
        data.push_back(imageNameHash);
        data.push_back(x);
        data.push_back(y);
        data.push_back(w);
        data.push_back(h);
        
        webSocket.write(boost::asio::buffer(data));
    }
    
    void SendTextDrawInstruction(
        WebSocket &webSocket,
        std::string_view text,
        PointF position,
        bool centerAlign) {
        
        const auto messageCode = MessageCodes::k_drawStringInstr;
        
        const auto x = (int)(position.x * NetConstants::k_floatPrecision);
        const auto y = (int)(position.y * NetConstants::k_floatPrecision);
        
        auto data = std::vector<int>();
        
        data.push_back(messageCode);
        data.push_back(x);
        data.push_back(y);
        data.push_back(centerAlign ? 1 : 0);
        
        data.push_back(text.length());
        
        for (auto c : text) {
            
            data.push_back((int)c);
        }
        
        webSocket.write(boost::asio::buffer(data));
    }
    
    void SendPresentCanvasInstruction(
        WebSocket &webSocket) {
        
        const auto messageCode = MessageCodes::k_applyBuffer;
        
        webSocket.write(
            boost::asio::buffer(&messageCode,sizeof(messageCode)));
    }
    
    void SendRequestImageDimensions(
        WebSocket &webSocket,
        int imageNameHash) {
        
        const auto messageCode = MessageCodes::k_requestImageDimensions;
        
        auto data = std::vector<int>();
        
        data.push_back(messageCode);
        data.push_back(imageNameHash);
        
        webSocket.write(boost::asio::buffer(data));
    }
}