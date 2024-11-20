/**
 * @file tx_vk_allocator.hpp
 * @author xmmmmmovo
 * @date 2024-08-15
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "taixu/common/base/macro.hpp"
#include "taixu/common/designs/noncopyable.hpp"

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

TX_NAMESPACE_BEGIN

class VKAllocator final : public Noncopyable {
public:
    VKAllocator() = delete;

    VKAllocator(const VKAllocator&)            = delete;
    VKAllocator& operator=(const VKAllocator&) = delete;

    VKAllocator(VKAllocator&& other) noexcept : _allocator(std::exchange(other._allocator, VK_NULL_HANDLE)) {};
    VKAllocator& operator=(VKAllocator&& other) noexcept {
        std::swap(_allocator, other._allocator);
        return *this;
    };

    explicit VKAllocator(VmaAllocator allocator) : _allocator(allocator) {
    }

    ~VKAllocator() override {
        vmaDestroyAllocator(_allocator);
    }

    static VKAllocator createAllocator();

private:
    VmaAllocator _allocator{VK_NULL_HANDLE};
};


TX_NAMESPACE_END
