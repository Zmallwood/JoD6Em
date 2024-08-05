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
#include "ServerCore/UserGameInstance/CoreGameObjects/Player.hpp"
#include "ServerCore/UserGameInstance/Cursor/Cursor.hpp"
#include "ServerCore/ServerWide/AssetsInformation/ImageDimensions.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
using tcp = boost::asio::ip::tcp;

namespace JoD {
    
    UserConnection::UserConnection(tcp::socket socket)
        : m_userGameInstanceEngine(std::make_shared<UserGameInstanceEngine>(
                                       *this)),
        m_player(std::make_shared<Player>()),
        m_cursor(std::make_shared<Cursor>(*this)){
        
        std::thread(
            &UserConnection::DoSession, this,
            std::move(socket)).detach();
    }
    
    void UserConnection::DoSessionNested(WebSocket* ws) {
        
        try {
            
            while (true){
                
                beast::flat_buffer buffer;     // This buffer will hold the incoming message.
                ws->read(buffer);     // Read a message.
                const auto message = buffer_cast<int *>(buffer.data());
                
                if (*message == MessageCodes::k_canvasSize){
                    
                    auto width = (int)message[1];
                    auto height = (int)message[2];
                    m_canvasSize = {width, height};
                }else if (*message == MessageCodes::k_leftMouseDown) {
                    
                    m_userGameInstanceEngine->m_mouseInput->
                    RegisterMouseDown(
                        MouseButtons::Left);
                }else if (*message == MessageCodes::k_rightMouseDown) {
                    
                    m_userGameInstanceEngine->m_mouseInput->
                    RegisterMouseDown(
                        MouseButtons::Right);
                }else if (*message == MessageCodes::k_mousePosition) {
                    
                    auto x = message[1] / net_constants::k_floatPrecision;
                    auto y = message[2] / net_constants::k_floatPrecision;
                    m_mousePosition = {x, y};
                }else if (*message == MessageCodes::k_provideImageDimensions) {
                    
                    auto imageNameHash = (int)message[1];
                    auto width = (int)message[2];
                    auto height = (int)message[3];
                    
                    _<ImageDimensions>().m_dimensions[imageNameHash] = {width, height};
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
            websocket::stream<tcp::socket> ws{std::move(socket)};
            
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
                
                std::this_thread::sleep_for(std::chrono::milliseconds(140));
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
        WebSocket &ws,
        std::string_view
        imageName,
        RectF destination) const {
        
        SendImageDrawInstruction(ws, Hash(imageName), destination);
    }
    
    void UserConnection::SendImageDrawInstruction(
        WebSocket &ws,
        int imageNameHash,
        RectF destination) const {
        
        auto msg_code = MessageCodes::k_drawImageInstr;
        
        auto x = (int)(destination.x * net_constants::k_floatPrecision);
        auto y = (int)(destination.y * net_constants::k_floatPrecision);
        auto w = (int)(destination.w * net_constants::k_floatPrecision);
        auto h = (int)(destination.h * net_constants::k_floatPrecision);
        
        auto data = std::vector<int>();
        
        data.push_back(msg_code);
        data.push_back(imageNameHash);
        data.push_back(x);
        data.push_back(y);
        data.push_back(w);
        data.push_back(h);
        
        ws.write(boost::asio::buffer(data));
    }
    
    void UserConnection::SendTextDrawInstruction(
        WebSocket &ws,
        std::string_view text,
        PointF position) const {
        
        auto msg_code = MessageCodes::k_drawStringInstr;
        
        auto x = (int)(position.x * net_constants::k_floatPrecision);
        auto y = (int)(position.y * net_constants::k_floatPrecision);
        
        auto data = std::vector<int>();
        
        data.push_back(msg_code);
        data.push_back(x);
        data.push_back(y);
        
        data.push_back(text.length());
        
        for (auto c : text) {
            
            data.push_back((int)c);
        }
        
        ws.write(boost::asio::buffer(data));
    }
    
    void UserConnection::SendPresentCanvasInstruction(WebSocket &ws) const {
        
        auto msg_code_present = MessageCodes::k_applyBuffer;
        
        ws.write(
            boost::asio::buffer(&msg_code_present,sizeof(msg_code_present)));
    }
    
    void UserConnection::SendRequestImageDimensions(WebSocket &ws,
                                                    int imageNameHash) const {
        auto msg_code = MessageCodes::k_requestImageDimensions;
        
        auto data = std::vector<int>();
        
        data.push_back(msg_code);
        data.push_back(imageNameHash);
        
        ws.write(boost::asio::buffer(data));
    }
    
    float UserConnection::GetAspectRatio() const {
        
        return static_cast<float>(m_canvasSize.w) / m_canvasSize.h;
    }
}