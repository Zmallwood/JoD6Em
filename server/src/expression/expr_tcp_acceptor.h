/*
 * expr_tcp_acceptor.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class expr_tcp_acceptor : public expr {
    public:
        expr_tcp_acceptor(std::shared_ptr<expr> expr_io_net_context,
                          std::shared_ptr<expr> expr_socket_address,
                          std::shared_ptr<expr> expr_socket_port);
        
        expr_return_struct eval() override;
        
    private:
        std::shared_ptr<expr> m_expr_io_net_context;
        std::shared_ptr<expr> m_expr_socket_address;
        std::shared_ptr<expr> m_expr_socket_port;
        boost::asio::ip::tcp::acceptor m_acceptor;
    };
}