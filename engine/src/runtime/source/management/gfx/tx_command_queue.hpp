/**
 * @file tx_command_queue.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-26
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */
#pragma once

#include "common/container/ring_buffer.hpp"
#include "taixu/common/base/macro.hpp"
#include "tx_command.hpp"

TX_NAMESPACE_BEGIN

/**
 * @brief CommandQueue
 *
 */
struct TXCommandQueue {
private:
    static constexpr uint16_t              MAX_COMMAND_QUEUE_SIZE = 256;
    RingBuffer<pro::proxy<TXCommandProxy>> _command_queue{MAX_COMMAND_QUEUE_SIZE};

public:
    void push(pro::proxy<TXCommandProxy> command);

    void update(float delta_time);
};

TX_NAMESPACE_END
