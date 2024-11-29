/**
 * @file ring_buffer.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-26
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */
#pragma once

#include "common/hal/tx_container.hpp"
#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN
/**
 * @brief A circle queue.
 *
 * @tparam T
 */
template<typename T>
class RingBuffer {
private:
    tx_vector<T>        _buffer{};
    size_t              _capacity{0};
    std::atomic<size_t> _head{0};
    std::atomic<size_t> _tail{0};

public:
    explicit RingBuffer(size_t const cap) : _capacity(cap), _buffer(cap) {
    }

    bool push(T&& item) {
        size_t current_tail = _tail.load(std::memory_order_relaxed);
        size_t next_tail    = (current_tail + 1) % _capacity;

        if (next_tail == _head.load(std::memory_order_acquire)) {
            // 缓冲区已满
            return false;
        }

        _buffer[current_tail] = std::forward<T>(item);
        _tail.store(next_tail, std::memory_order_release);
        return true;
    }

    std::optional<T> pop() {
        size_t current_head = _head.load(std::memory_order_relaxed);

        if (current_head == _tail.load(std::memory_order_acquire)) {
            // 缓冲区为空
            return std::nullopt;
        }

        T item = std::move(_buffer[current_head]);
        _head.store((current_head + 1) % _capacity, std::memory_order_release);
        return item;
    }

    bool isEmpty() const {
        return _head.load(std::memory_order_acquire) == _tail.load(std::memory_order_acquire);
    }

    bool isFull() const {
        return (_tail.load(std::memory_order_acquire) + 1) % _capacity == _head.load(std::memory_order_acquire);
    }
};

TX_NAMESPACE_END
