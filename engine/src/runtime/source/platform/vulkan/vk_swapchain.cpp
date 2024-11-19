/**
 * @file vk_swapchain.cpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-20
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#include "vk_swapchain.hpp"

TX_NAMESPACE_BEGIN

ResValT<VKSwapchain> VKSwapchain::createSwapchain(vk::raii::PhysicalDevice const& physical_device,
                                                  vk::raii::SurfaceKHR const& surface, vk::raii::Device const& device,
                                                  const Window* window, const tx_vector<uint32_t>& queue_family_indices,
                                                  vk::PresentModeKHR present_mode) {
    VKSwapchain swapchain;
    return swapchain;
}

TX_NAMESPACE_END
