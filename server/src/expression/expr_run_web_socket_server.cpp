/*
 * expr_run_web_socket_server.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_run_web_socket_server.h"
#include "server_core/net/web_socket_server.h"
#include "server_core/net/user_connection.h"
#include "expr_io_net_context.h"
#include "expr_tcp_acceptor.h"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

namespace jod {
    expr_run_web_socket_server::expr_run_web_socket_server(
        std::shared_ptr<expr_string> expression_socket_address,
        std::
        shared_ptr<expr_string> expression_socket_port)
        : m_expr_socket_address(expression_socket_address),
        m_expr_socket_port(expression_socket_port){
        
    }
    
    expr_return_struct expr_run_web_socket_server::eval() {
        auto socket_address =
            std::any_cast<std::string>(
                m_expr_socket_address->eval().data);
        auto socket_port =
            std::any_cast<std::string>(
                m_expr_socket_port->eval().data);
        
        auto const address =
            net::ip::make_address(socket_address);
        auto const port =
            static_cast<unsigned short>(std::atoi(socket_port.c_str()));

        auto expr_io_net_context_obj = std::make_shared<expr_io_net_context>();
        auto expr_tcp_acceptor_obj = std::make_shared<expr_tcp_acceptor>(expr_io_net_context_obj, m_expr_socket_address, m_expr_socket_port);

        // auto& ioc = *std::any_cast<std::shared_ptr<net::io_context>>(expr_io_net_context_obj->eval().data);

        // tcp::acceptor acceptor{ioc, {address, port}}; // The acceptor receives incoming connections.
        while (true){
            tcp::socket socket{*std::any_cast<std::shared_ptr<net::io_context>>(expr_io_net_context_obj->eval().data)}; // This will receive the new connection.
            std::any_cast<std::reference_wrapper<tcp::acceptor>>(expr_tcp_acceptor_obj->eval().data).get().accept(socket); // Block until we get a connection.
            m_user_connections.push_back(
                std::make_shared<user_connection>(
                    std::move(socket)));
        }
        
        return {0};
    }
}