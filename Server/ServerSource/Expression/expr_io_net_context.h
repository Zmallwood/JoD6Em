/*
 * expr_io_net_context.h
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    class expr_io_net_context : public expr {
    public:
        expr_io_net_context();

        expr_return_struct eval() override;
        
    private:
        std::shared_ptr<boost::asio::io_context> m_ioc;
    };
}