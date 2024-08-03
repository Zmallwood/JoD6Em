/*
 * expr_io_net_context.cpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "expr_io_net_context.h"

namespace jod {
    expr_io_net_context::expr_io_net_context()
        : m_ioc(std::make_shared<boost::asio::io_context>(1)) {
    }
    
    expr_return_struct expr_io_net_context::eval() {
        return {0, m_ioc};
    }
}