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
        UserID userID;
    };
    
    UserConnection::UserConnection(Socket socket) : m_pImpl(std::make_unique<Impl>()) {
        
        m_pImpl->userID = _<EngineGet>().RegisterEngineInstance();
        
        std::cout << "User connected, got ID: " << m_pImpl->userID << std::endl;
                
        std::thread(
            &UserConnection::DoSession, this, m_pImpl->userID,
            std::move(socket)).detach();
    }
    
    UserConnection::~UserConnection() {
        
    }
    
    void UserConnection::DoSessionNested(WebSocket* webSocket) {
        
        try {
            
            while (true){
                
                flat_buffer buffer; // This buffer will hold the incoming message.
                webSocket->read(buffer); // Read a message.
                const auto data = buffer_cast<int *>(buffer.data());
                
                if (*data == MessageCodes::k_canvasSize){
                    
                    const auto width = (int)data[1];
                    const auto height = (int)data[2];
                    _<EngineGet>().GetInstance(m_pImpl->userID)->SetCanvasSize({width, height});
                }else if (*data == MessageCodes::k_leftMouseDown) {
                    
                    _<EngineGet>().GetInstance(m_pImpl->userID)->GetMouseInput()->
                    RegisterMouseDown(
                        MouseButtons::Left);
                }else if (*data == MessageCodes::k_leftMouseUp) {
                    
                    _<EngineGet>().GetInstance(m_pImpl->userID)->GetMouseInput()->
                    RegisterMouseUp(
                        MouseButtons::Left);
                }else if (*data == MessageCodes::k_rightMouseDown) {
                    
                    _<EngineGet>().GetInstance(m_pImpl->userID)->GetMouseInput()->
                    RegisterMouseDown(
                        MouseButtons::Right);
                }else if (*data == MessageCodes::k_rightMouseUp) {
                    
                    _<EngineGet>().GetInstance(m_pImpl->userID)->GetMouseInput()->
                    RegisterMouseUp(
                        MouseButtons::Right);
                }else if (*data == MessageCodes::k_mousePosition) {
                    
                    const auto x = data[1] / NetConstants::k_floatPrecision;
                    const auto y = data[2] / NetConstants::k_floatPrecision;
                    _<EngineGet>().GetInstance(m_pImpl->userID)->SetMousePosition({x, y});
                }else if (*data == MessageCodes::k_provideImageDimensions) {
                    
                    const auto imageNameHash = (int)data[1];
                    const auto width = (int)data[2];
                    const auto height = (int)data[3];
                    
                    _<ImageDimensions>().SetDimension(
                        imageNameHash,
                        {width, height});
                }
            }
        }
        catch (const std::exception& ex) {
            
            std::cout << "Exception: " << ex.what() << std::endl;
            
            return;
        }
    }
    
    void UserConnection::DoSession(UserID userID, Socket socket) {
        
        try{
            
            // Construct the stream by moving in the socket.
            WebSocket webSocket{std::move(socket)};
            
            // Set a decorator to change the Server of the handshake.
            webSocket.set_option(
                websocket::stream_base::decorator(
                    [](websocket::response_type &res){
                        
                        res.set(
                            http::field::server,
                            std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-server-sync");
                    }));
            
            webSocket.accept(); // Accept the websocket handshake.
            
            webSocket.text(false); // Receive binary data, not text.
            
            std::thread(
                &UserConnection::DoSessionNested, this,
                &webSocket).detach();
            
            while (true){
                
                _<EngineGet>().GetInstance(m_pImpl->userID)->Update(userID);
                _<EngineGet>().GetInstance(m_pImpl->userID)->Render(userID, webSocket);
                
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
}