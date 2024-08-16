/*
 * UserConnection.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "UserConnection.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "MessageCodes.hpp"
#include "ServerCore/ServerWide/AssetsInformation/ImageDimensions.hpp"
#include "ServerCore/UserGameInstance/EngineInstance.hpp"
#include "ServerCore/ServerWide/EngineGet.hpp"

using namespace boost::beast;

namespace JoD {
    
    struct UserConnection::Impl {
        
        UserID userID; // Unique ID for every connected user.
    };
    
    UserConnection::UserConnection(Socket socket)
        : m_pImpl(std::make_unique<Impl>()) {
        
        // Register the new user with its socket object and obtain its user ID.
        m_pImpl->userID =
            _<EngineGet>().CreateNewEngineInstance(std::move(socket));
        
        // Get the web socket object for the new user.
        auto webSocket = _<EngineGet>().GetWebSocket(m_pImpl->userID);
        
        // Notify about the new user connection.
        std::cout << "User connected, got ID: " << m_pImpl->userID << std::endl;
        
        // Set a decorator to change the Server of the handshake.
        webSocket->set_option(
            websocket::stream_base::decorator(
                [](websocket::response_type &res){
                    
                    res.set(
                        http::field::server,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-sync");
                }));
        
        // Accept the websocket handshake.
        webSocket->accept();
        
        // Receive binary data, not text.
        webSocket->text(false);
        
        // Start listening for incoming messages in separate thread.
        std::thread(
            &UserConnection::HandleIncoming, this,
            webSocket).detach();
        
        // Run users game loop in separate thread.
        std::thread(
            &UserConnection::RunUserGameLoop, this, m_pImpl->userID).detach();
    }
    
    UserConnection::~UserConnection() {}
    
    void UserConnection::RunUserGameLoop(UserID userID) {
        
        try{
            
            while (true){
                
                // Update users game state.
                _<EngineGet>().GetEngineInstance(m_pImpl->userID)->Update(
                    userID);
                
                // Render users game state.
                _<EngineGet>().GetEngineInstance(m_pImpl->userID)->Render(
                    userID);
                
                // Slow down the loop rate.
                std::this_thread::sleep_for(std::chrono::milliseconds(70));
            }
        }
        catch (system_error const &se){
            
            // This indicates that the session was closed.
            if (se.code() != websocket::error::closed) {
                
                std::cerr << "Error: " << se.code().message() << std::endl;
            }
        }
        catch (std::exception const &e){
            
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    void UserConnection::HandleIncoming(WebSocket* webSocket) {
        
        try {
            
            while (true){
                
                // This buffer will hold the incoming message.
                flat_buffer buffer;
                
                // Read a message.
                webSocket->read(buffer);
                
                // Cast the recieved data to int array.
                const auto data = buffer_cast<int *>(buffer.data());
                
                auto engineInstance =
                    _<EngineGet>().GetEngineInstance(m_pImpl->userID);
                
                // Check the first int in the recieved data,
                // which contains the message code.
                
                if (*data == MessageCodes::k_canvasSize){
                    
                    // Extract the data components.
                    
                    const auto width = (int)data[1];
                    const auto height = (int)data[2];
                    
                    // Set the users canvas size to the recieved dimensions.
                    
                    engineInstance->SetCanvasSize({width, height});
                }
                else if (*data == MessageCodes::k_leftMouseDown) {
                    
                    // Register left mouse button as pressed down.
                    
                    engineInstance->GetMouseInput()->RegisterMouseDown(
                        MouseButtons::Left);
                }
                else if (*data == MessageCodes::k_leftMouseUp) {
                    
                    // Register left mouse button as released.
                    
                    engineInstance->GetMouseInput()->RegisterMouseUp(
                        MouseButtons::Left);
                }
                else if (*data == MessageCodes::k_rightMouseDown) {
                    
                    // Register right mouse button as pressed down.
                    
                    engineInstance->GetMouseInput()->RegisterMouseDown(
                        MouseButtons::Right);
                }
                else if (*data == MessageCodes::k_rightMouseUp) {
                    
                    // Register right mouse button as released.
                    
                    engineInstance->GetMouseInput()->RegisterMouseUp(
                        MouseButtons::Right);
                }
                else if (*data == MessageCodes::k_mousePosition) {
                    
                    // Extract the data components.
                    
                    const auto x = data[1] / NetConstants::k_floatPrecision;
                    const auto y = data[2] / NetConstants::k_floatPrecision;
                    
                    // Set the users mouse position to the new value.
                    
                    engineInstance->SetMousePosition({x, y});
                }
                else if (*data == MessageCodes::k_provideImageDimensions) {
                    
                    // Extract the data components.
                    
                    const auto imageNameHash = (int)data[1];
                    const auto width = (int)data[2];
                    const auto height = (int)data[3];
                    
                    // Set the images dimensions to the recieved value.
                    
                    _<ImageDimensions>().SetDimension(
                        imageNameHash,
                        {width, height});
                }
            }
        }
        catch (const std::exception& ex) {
            
            // Notify if something went wrong.
            
            std::cout << "Exception: " << ex.what() << std::endl;
            
            return;
        }
    }
}