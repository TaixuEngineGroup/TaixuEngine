/**
 * @file tx_allocator.hpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-07-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <functional>
#include <memory>

#include <mimalloc.h>

namespace taixu {

template<typename T>
using txAllocatorT = mi_stl_allocator<T>;

/**
 * @brief 自定义unique_ptr
 *
 * @tparam T
 */
template<typename T>
using TXUniquePtr = std::unique_ptr<T, std::function<void(T*)>>;

/**
 * @brief create unique_ptr by tx allocator
 *
 * @tparam T
 * @tparam Args
 * @param args
 * @return constexpr std::unique_ptr<T, std::function<void(T*)>>
 */
template<typename T, typename... Args>
[[nodiscard]] constexpr TXUniquePtr<T> makeTXUnique(Args&&... args) {
    using AllocatorTraits = std::allocator_traits<txAllocatorT<T>>;

    struct Deleter {
        txAllocatorT<T> alloc{};
        void            operator()(T* obj) const {
            AllocatorTraits::deallocate(alloc, obj, 1);
        }
    };
    Deleter deleter{};

    TXUniquePtr<T> obj(AllocatorTraits::allocate(deleter.alloc, 1), deleter);
    AllocatorTraits::construct(deleter.alloc, obj.get(), std::forward<Args>(args)...);
    TX_ASSERT(obj != nullptr);
    return obj;
}

}// namespace taixu
