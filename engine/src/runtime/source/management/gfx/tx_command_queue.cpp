/**
 * @file tx_command_queue.cpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-27
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */
#include "tx_command_queue.hpp"

TX_NAMESPACE_BEGIN


void TXCommandQueue::push(pro::proxy<TXCommandProxy> command) {
    _command_queue.push(std::move(command));
}

void TXCommandQueue::update(float delta_time) {
    while (!_command_queue.isEmpty()) {
        auto command = _command_queue.pop();
        // command->execute(delta_time);
    }
}


TX_NAMESPACE_END
