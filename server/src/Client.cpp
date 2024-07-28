// Copyright (c) 2024 Andreas Åkerberg.

#include "Client.h"

#include "Net.h"

#include "ClientCore.h"

#include "MessageCodes.h"

#include "NetConfiguration.h"

namespace beast = boost::beast;

namespace http = beast::http;

namespace websocket = beast::websocket;

using tcp = boost::asio::ip::tcp;

namespace jod
{
  Client::Client(tcp::socket socket) : m_serverEngine(std::make_shared<ServerEngine>(*this))
  {
    std::thread(&Client::DoSession, this, std::move(socket)).detach();
  }

  void Client::DoSession(tcp::socket socket)
  {
    try
    {
      /* Construct the stream by moving in the socket. */

      websocket::stream<tcp::socket> ws{std::move(socket)};

      /* Set a decorator to change the Server of the handshake. */

      ws.set_option(websocket::stream_base::decorator(
          [](websocket::response_type &res)
          {
            res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) + " websocket-server-sync");
          }));

      /* Accept the websocket handshake. */

      ws.accept();

      ws.text(false);

      while (true)
      {
        m_serverEngine->Update();
        m_serverEngine->Render(ws);

        /* This buffer will hold the incoming message. */

        beast::flat_buffer buffer;

        /* Read a message. */

        ws.read(buffer);

        const auto message = buffer_cast<int *>(buffer.data());

        if (*message == MessageCodes::k_canvasSize)
        {
          auto w = (int)message[1];
          auto h = (int)message[2];
          m_canvasSize = {w, h};
          std::cout << "Recieved canvas size: " << w << ", " << h << std::endl;
        }
        else if (*message == MessageCodes::k_tick)
        {
          // SendImageDrawInstruction(ws, "DefaultSceneBackground",
          //                          {0.0f, 0.0f, 1.0f, 1.0f});
          // SendImageDrawInstruction(ws, "JoDLogo", {0.3f, 0.3f, 0.4f, 0.2f});
          // SendPresentCanvasInstruction(ws);
        }
        else if (*message == MessageCodes::k_mouseDown)
        {
          m_serverEngine->OnMouseDown();
        }
      }
    }
    catch (beast::system_error const &se)
    {
      /* This indicates that the session was closed. */

      if (se.code() != websocket::error::closed)
        std::cerr << "Error: " << se.code().message() << std::endl;
    }
    catch (std::exception const &e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }

  void Client::SendImageDrawInstruction(websocket::stream<tcp::socket> &ws,
                                        std::string_view imageName, RectF dest)
  {
    SendImageDrawInstruction(ws, Hash(imageName), dest);
  }

  void Client::SendImageDrawInstruction(websocket::stream<tcp::socket> &ws,
                                        int imageNameHash, RectF dest)
  {
    auto msg_code = MessageCodes::k_drawImageInstr;

    auto x = (int)(dest.x * NetConstants::k_floatPrecision);
    auto y = (int)(dest.y * NetConstants::k_floatPrecision);
    auto w = (int)(dest.w * NetConstants::k_floatPrecision);
    auto h = (int)(dest.h * NetConstants::k_floatPrecision);

    auto data = std::vector<int>();

    data.push_back(msg_code);
    data.push_back(imageNameHash);
    data.push_back(x);
    data.push_back(y);
    data.push_back(w);
    data.push_back(h);

    ws.write(boost::asio::buffer(data));
  }

  void Client::SendPresentCanvasInstruction(websocket::stream<tcp::socket> &ws)
  {
    auto msg_code_present = MessageCodes::k_applyBuffer;

    ws.write(boost::asio::buffer(&msg_code_present, sizeof(msg_code_present)));
  }

  float Client::GetAspectRatio()
  {
    return static_cast<float>(m_canvasSize.w) / m_canvasSize.h;
  }
}