/*
 * UserConnection.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "UserConnection.hpp"
#include "ServerCore/Net/WebSocketServer.hpp"
#include "ServerCore/UserGameInstance/Input/Mouse/MouseInput.hpp"
#include "ServerCore/UserGameInstance/UserGameInstanceEngine.hpp"
#include "MessageCodes.hpp"
#include "NetConfiguration.hpp"
#include "ServerCore/ServerWide/AssetsInformation/ImageDimensions.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace JoD {
    
    UserConnection::UserConnection(tcp::socket socket)
        : m_userGameInstanceEngine(
            std::make_shared<UserGameInstanceEngine>(
                *this)){
        
        std::thread(
            &UserConnection::DoSession, this,
            std::move(socket)).detach();
    }
    
    void UserConnection::DoSessionNested(WebSocket* webSocket) {
        
        try {
            
            while (true){
                
                beast::flat_buffer buffer;     // This buffer will hold the incoming message.
                webSocket->read(buffer);     // Read a message.
                const auto data = buffer_cast<int *>(buffer.data());
                
                if (*data == MessageCodes::k_canvasSize){
                    
                    auto width = (int)data[1];
                    auto height = (int)data[2];
                    m_userGameInstanceEngine->m_canvasSize = {width, height};
                }else if (*data == MessageCodes::k_leftMouseDown) {
                    
                    m_userGameInstanceEngine->m_mouseInput->
                    RegisterMouseDown(
                        MouseButtons::Left);
                }else if (*data == MessageCodes::k_rightMouseDown) {
                    
                    m_userGameInstanceEngine->m_mouseInput->
                    RegisterMouseDown(
                        MouseButtons::Right);
                }else if (*data == MessageCodes::k_mousePosition) {
                    
                    auto x = data[1] / NetConstants::k_floatPrecision;
                    auto y = data[2] / NetConstants::k_floatPrecision;
                    m_userGameInstanceEngine->m_mousePosition = {x, y};
                }else if (*data == MessageCodes::k_provideImageDimensions) {
                    
                    auto imageNameHash = (int)data[1];
                    auto width = (int)data[2];
                    auto height = (int)data[3];
                    
                    _<ImageDimensions>().m_dimensions[imageNameHash] = {width,
                                                                        height};
                }
            }
        }
        catch (const std::exception& ex) {
            
            std::cout << "Exception: " << ex.what() << std::endl;
            
            return;
        }
    }
    
    void UserConnection::DoSession(tcp::socket socket) {
        
        try{
            
            // Construct the stream by moving in the socket.
            WebSocket ws{std::move(socket)};
            
            // Set a decorator to change the Server of the handshake.
            ws.set_option(
                websocket::stream_base::decorator(
                    [](websocket::response_type &res){
                        
                        res.set(
                            http::field::server,
                            std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-server-sync");
                    }));
            
            ws.accept(); // Accept the websocket handshake.
            
            ws.text(false); // Receive binary data, not text.
            
            std::thread(&UserConnection::DoSessionNested, this, &ws).detach();
            
            while (true){
                
                m_userGameInstanceEngine->Update();
                m_userGameInstanceEngine->Render(ws);
                
                std::this_thread::sleep_for(std::chrono::milliseconds(70));
            }
        }
        catch (beast::system_error const &se){
            
            // This indicates that the session was closed.
            if (se.code() != websocket::error::closed) {
                
                std::cerr << "Error: " << se.code().message() << std::endl;
            }
        }
        catch (std::exception const &e){
            
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    void UserConnection::SendImageDrawInstruction(
        WebSocket &webSocket,
        std::string_view
        imageName,
        BoxF destination) const {
        
        SendImageDrawInstruction(webSocket, Hash(imageName), destination);
    }
    
    void UserConnection::SendImageDrawInstruction(
        WebSocket &webSocket,
        int imageNameHash,
        BoxF destination) const {
        
        auto messageCode = MessageCodes::k_drawImageInstr;
        
        auto x = (int)(destination.x * NetConstants::k_floatPrecision);
        auto y = (int)(destination.y * NetConstants::k_floatPrecision);
        auto w = (int)(destination.w * NetConstants::k_floatPrecision);
        auto h = (int)(destination.h * NetConstants::k_floatPrecision);
        
        auto data = std::vector<int>();
        
        data.push_back(messageCode);
        data.push_back(imageNameHash);
        data.push_back(x);
        data.push_back(y);
        data.push_back(w);
        data.push_back(h);
        
        webSocket.write(boost::asio::buffer(data));
    }
    
    void UserConnection::SendTextDrawInstruction(
        WebSocket &webSocket,
        std::string_view text,
        PointF position) const {
        
        auto messageCode = MessageCodes::k_drawStringInstr;
        
        auto x = (int)(position.x * NetConstants::k_floatPrecision);
        auto y = (int)(position.y * NetConstants::k_floatPrecision);
        
        auto data = std::vector<int>();
        
        data.push_back(messageCode);
        data.push_back(x);
        data.push_back(y);
        
        data.push_back(text.length());
        
        for (auto c : text) {
            
            data.push_back((int)c);
        }
        
        webSocket.write(boost::asio::buffer(data));
    }
    
    void UserConnection::SendPresentCanvasInstruction(
        WebSocket &webSocket) const {
        
        auto messageCode = MessageCodes::k_applyBuffer;
        
        webSocket.write(
            boost::asio::buffer(&messageCode,sizeof(messageCode)));
    }
    
    void UserConnection::SendRequestImageDimensions(WebSocket &webSocket,
                                                    int imageNameHash) const {
        auto messageCode = MessageCodes::k_requestImageDimensions;
        
        auto data = std::vector<int>();
        
        data.push_back(messageCode);
        data.push_back(imageNameHash);
        
        webSocket.write(boost::asio::buffer(data));
    }
}