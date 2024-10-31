/**
 * @file vk_utils.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-10-27
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "taixu/common/base/macro.hpp"

#include <vulkan/vulkan_to_string.hpp>

TX_NAMESPACE_BEGIN

// define concept vk type that can use in vk::to_string
template<typename T>
concept VKStringable = requires(T t) { vk::to_string(t); };

/**
 * @brief get the queue family index
 *
 * @param device
 * @param surface
 * @param props
 * @param flags
 * @return std::optional<uint32_t>
 */
std::optional<uint32_t> findQueueFamily(vk::raii::PhysicalDevice const& device, vk::raii::SurfaceKHR const& surface,
                                        std::vector<vk::QueueFamilyProperties> const& props,
                                        std::optional<vk::QueueFlagBits>              flag_opt) noexcept;

TX_NAMESPACE_END
