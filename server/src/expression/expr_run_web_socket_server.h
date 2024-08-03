/*
 * expr_run_web_socket_server.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

#include "expr_string.h"

namespace jod {
    class user_connection;

    class expr_run_web_socket_server : public expr {
    public:
        expr_run_web_socket_server(
            std::shared_ptr<expr_string> expression_socket_address,
            std::shared_ptr<expr_string>
            expression_socket_port);
        
        expr_return_struct evaluate();
        
    private:
        std::shared_ptr<expr> m_expression_socket_address;
        std::shared_ptr<expr> m_expression_socket_port;
        std::vector<std::shared_ptr<user_connection> > m_user_connections;
    };
}