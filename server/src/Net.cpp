#include "Net.h"

#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/assert/source_location.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <cstdlib>
#include <string>
#include <thread>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace jod
{
    // Echoes back all received WebSocket messages
    void do_session(tcp::socket socket)
    {
        try
        {
            // Construct the stream by moving in the socket
            websocket::stream<tcp::socket> ws{std::move(socket)};

            // Set a decorator to change the Server of the handshake
            ws.set_option(websocket::stream_base::decorator(
                [](websocket::response_type &res)
                { res.set(http::field::server, std::string(BOOST_BEAST_VERSION_STRING) + " websocket-server-sync"); }));

            // Accept the websocket handshake
            ws.accept();

            for (;;)
            {
                // This buffer will hold the incoming message
                beast::flat_buffer buffer;

                // Read a message
                ws.read(buffer);

                std::cout << "Recieved: "
                          << std::string(buffer_cast<const char *>(buffer.data()), buffer.size()) + "\n";

                auto s = std::string(buffer_cast<const char *>(buffer.data()), buffer.size());
                if (s == "Tick")
                {
                    std::cout << "Send drawimg request.\n";
                    const int k_drawImageInstr = 1;
                    const int k_presentCanvas = 2;

                    auto msg_code = k_drawImageInstr;
                    auto imageNamHash = Hash("DefaultSceneBackground");
                    auto x = (int)(0.0f * 10000);
                    auto y = (int)(0.0f * 10000);
                    auto w = (int)(1.0f * 10000);
                    auto h = (int)(1.0f * 10000);

                    auto data = std::vector<int>();
                    data.push_back(msg_code);
                    data.push_back(imageNamHash);
                    data.push_back(x);
                    data.push_back(y);
                    data.push_back(w);
                    data.push_back(h);

                    ws.write(boost::asio::buffer(data));

                    msg_code = k_drawImageInstr;
                    imageNamHash = Hash("JoDLogo");
                    x = (int)(0.3f * 10000);
                    y = (int)(0.3f * 10000);
                    w = (int)(0.4f * 10000);
                    h = (int)(0.2f * 10000);

                    data = std::vector<int>();
                    data.push_back(msg_code);
                    data.push_back(imageNamHash);
                    data.push_back(x);
                    data.push_back(y);
                    data.push_back(w);
                    data.push_back(h);

                    ws.write(boost::asio::buffer(data));

                    auto msg_code_present = k_presentCanvas;
                    ws.write(boost::asio::buffer(&msg_code_present, sizeof(msg_code_present)));

                    // std::cout << "a.\n";
                    // auto p =
                    //     ((int)h << 5*4) + ((int)w << 4 * 4) + ((int)y << 3 * 4) + ((int)x << 2 * 4) + (imageNamHash
                    //     << 1 * 4) + msg_code;
                    // std::cout << "b.\n";
                    // ws.write(boost::asio::buffer(&msg_code, sizeof(msg_code)));
                    // ws.write(boost::asio::buffer(&imageNamHash, sizeof(imageNamHash)));
                    // ws.write(boost::asio::buffer(&x, sizeof(x)));
                    // ws.write(boost::asio::buffer(&y, sizeof(y)));
                    // ws.write(boost::asio::buffer(&w, sizeof(w)));
                    // ws.write(boost::asio::buffer(&h, sizeof(h)));
                    // std::cout << "c.\n";
                }

                ws.text(false);
                // ws.write(boost::asio::buffer(std::string("Hello world!")));
                // int i = 12345;
                // ws.write(boost::asio::buffer(&i, sizeof(i)));
                // ws.write(buffer.data());
            }
        }
        catch (beast::system_error const &se)
        {
            // This indicates that the session was closed
            if (se.code() != websocket::error::closed)
                std::cerr << "Error: " << se.code().message() << std::endl;
        }
        catch (std::exception const &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void WebSocketServer::Start(std::string socketAddress, std::string socketPort)
    {
        auto const address = net::ip::make_address(socketAddress);
        auto const port = static_cast<unsigned short>(std::atoi(socketPort.c_str()));

        // The io_context is required for all I/O
        net::io_context ioc{1};

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {address, port}};
        for (;;)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            std::cout << "connection\n";

            // Launch the session, transferring ownership of the socket
            std::thread(&do_session, std::move(socket)).detach();
        }
    }
}