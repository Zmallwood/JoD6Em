/*
 * expr_run_web_socket_server.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_run_web_socket_server.h"
#include "server_core/net/web_socket_server.h"
#include "server_core/net/user_connection.h"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

namespace jod {
    expr_run_web_socket_server::expr_run_web_socket_server(
        std::shared_ptr<expr_string> expression_socket_address,
        std::
        shared_ptr<expr_string> expression_socket_port)
        : m_expression_socket_address(expression_socket_address),
        m_expression_socket_port(expression_socket_port){
        
    }
    
    expr_return_struct expr_run_web_socket_server::evaluate() {
        auto socket_address =
            std::any_cast<std::string>(
                m_expression_socket_address->evaluate().data);
        auto socket_port =
            std::any_cast<std::string>(
                m_expression_socket_port->evaluate().data);
        
        auto const address =
            net::ip::make_address(socket_address);
        auto const port =
            static_cast<unsigned short>(std::atoi(socket_port.c_str()));
        net::io_context ioc{1}; // The io_context is required for all I/O.
        tcp::acceptor acceptor{ioc, {address, port}}; // The acceptor receives incoming connections.
        while (true){
            tcp::socket socket{ioc}; // This will receive the new connection.
            acceptor.accept(socket); // Block until we get a connection.
            m_user_connections.push_back(
                std::make_shared<user_connection>(
                    std::move(socket)));
        }
        
        return {0};
    }
}