/**
 * @file vk_allocator.cpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-21
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#include "vk_allocator.hpp"

TX_NAMESPACE_BEGIN

VKAllocator VKAllocator::createAllocator() {


    return VKAllocator(VK_NULL_HANDLE);
}

TX_NAMESPACE_END
