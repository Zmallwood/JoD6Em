/*
 * InstructionsSending.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "InstructionsSending.hpp"
#include "MessageCodes.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

namespace JoD {

void SendImageDrawInstruction(
    UserID userID,
    std::string_view
    imageName,
    BoxF dest) {
    
// Forward function call to overload.
    SendImageDrawInstruction(userID, Hash(imageName), dest);
}

void SendImageDrawInstruction(
    UserID userID,
    int imageNameHash,
    BoxF dest) {
    
// Get websocket object for user.
    auto webSocket = _<EngineGet>().GetWebSocket(userID);
    
// Use message code for drawing images.
    const auto messageCode = MessageCodes::k_drawImageInstruction;
    
// Get destination rectangle values.
    const auto x = (int)(dest.x * NetConstants::k_floatPrecision);
    const auto y = (int)(dest.y * NetConstants::k_floatPrecision);
    const auto w = (int)(dest.w * NetConstants::k_floatPrecision);
    const auto h = (int)(dest.h * NetConstants::k_floatPrecision);
    
// To hold the data to send.
    auto data = std::vector<int>();
    
// Fill data with content.
    data.push_back(messageCode);
    data.push_back(imageNameHash);
    data.push_back(x);
    data.push_back(y);
    data.push_back(w);
    data.push_back(h);
    
// Send the data.
    webSocket->write(boost::asio::buffer(data));
}

void SendTextDrawInstruction(
    UserID userID,
    std::string_view text,
    PointF position,
    bool centerAlign) {
    
// Get websocket object for user.
    auto webSocket = _<EngineGet>().GetWebSocket(userID);
    
// Use message code for drawing text.
    const auto messageCode = MessageCodes::k_drawStringInstruction;
    
// Get position point values.
    const auto x = (int)(position.x * NetConstants::k_floatPrecision);
    const auto y = (int)(position.y * NetConstants::k_floatPrecision);
    
// To hold the data to send.
    auto data = std::vector<int>();
    
// Fill data with content.
    data.push_back(messageCode);
    data.push_back(x);
    data.push_back(y);
    data.push_back(centerAlign ? 1 : 0);
    
// Insert the length of the text to draw.
    data.push_back(text.length());
    
// Insert all characters one at a time to the message data.
    for (auto c : text) {
        
        data.push_back((int)c);
    }
    
// Send the data.
    webSocket->write(boost::asio::buffer(data));
}

void SendPresentCanvasInstruction(
    UserID userID) {
    
// Get websocket object for user.
    auto webSocket = _<EngineGet>().GetWebSocket(userID);
    
// Use message code for drawing text.
    const auto messageCode = MessageCodes::k_applyBuffer;
    
// Send the data.
    webSocket->write(
        boost::asio::buffer(&messageCode,sizeof(messageCode)));
}

void SendRequestImageDimensions(
    UserID userID,
    int imageNameHash) {
    
// Get websocket object for user.
    auto webSocket = _<EngineGet>().GetWebSocket(userID);
    
// Use message code for drawing text.
    const auto messageCode = MessageCodes::k_requestImageDimensions;
    
// To hold the data to send.
    auto data = std::vector<int>();
    
// Fill data with content.
    data.push_back(messageCode);
    data.push_back(imageNameHash);
    
// Send the data.
    webSocket->write(boost::asio::buffer(data));
}

void SendRequestImageDimensions(
    UserID userID,
    std::string_view imageName) {
    
// Forward the function call to overload.
    SendRequestImageDimensions(userID, Hash(imageName));
}

}