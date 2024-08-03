/*
 * expr_tcp_acceptor.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_tcp_acceptor.h"
#include <functional>

namespace jod {
    expr_tcp_acceptor::expr_tcp_acceptor(
        std::shared_ptr<expr> expr_io_net_context,
        std::shared_ptr<expr>
        expr_socket_address,
        std::shared_ptr<expr> expr_socket_port)
        : m_expr_io_net_context(expr_io_net_context),
        m_expr_socket_address(expr_socket_address),
        m_expr_socket_port(expr_socket_port),
        m_acceptor({
        *std::any_cast<std::shared_ptr<boost::asio::io_context>>(
            expr_io_net_context->eval().data),
        
        {
            boost::asio::ip::make_address(std::any_cast<std::string>(
                                              m_expr_socket_address
                                              ->eval().data)),
            static_cast<unsigned short>(std::stoi(
                                            std::any_cast<std::string>(
                                                m_expr_socket_port
                                                ->
                                                eval().data).
                                            c_str()))
        }}){
    }
    
    expr_return_struct expr_tcp_acceptor::eval() {
        return {0,
                std::reference_wrapper<boost::asio::ip::tcp::acceptor>(
                    m_acceptor)};
    }
}