/**
 * @file vk_swapchain.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-01
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "common/hal/tx_container.hpp"
#include "taixu/common/base/result.hpp"
#include "taixu/gameplay/gui/window.hpp"
TX_NAMESPACE_BEGIN

class VKSwapchain final {
public:
    vk::raii::SwapchainKHR swapchain{VK_NULL_HANDLE};
    vk::Extent2D           extent;
    vk::Format             swapchain_format;
    vk::PresentModeKHR     present_mode;

    std::vector<vk::raii::Image>     images;
    std::vector<vk::raii::ImageView> image_views;

    // RetCode initSwapchain(vk::raii::PhysicalDevice const& physical_device, vk::raii::SurfaceKHR const& surface,
    //                       vk::raii::Device const& device, const Window* window,
    //                       const tx_vector<uint32_t>& queue_family_indices, vk::PresentModeKHR present_mode);

    // RetCode recreateSwapchain(vk::raii::PhysicalDevice const& physical_device, vk::raii::SurfaceKHR const& surface,
    //                           vk::raii::Device const& device, const Window* window,
    //                           const tx_vector<uint32_t>& queue_family_indices, vk::PresentModeKHR present_mode);

    static ResValT<VKSwapchain> createSwapchain(vk::raii::PhysicalDevice const& physical_device,
                                                vk::raii::SurfaceKHR const& surface, vk::raii::Device const& device,
                                                const Window* window, const tx_vector<uint32_t>& queue_family_indices,
                                                vk::PresentModeKHR present_mode = vk::PresentModeKHR::eFifo);
};

TX_NAMESPACE_END
