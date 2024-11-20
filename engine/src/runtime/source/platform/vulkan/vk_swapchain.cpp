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
#include "common/log/custom_fmt.hpp"
#include "taixu/common/log/logger.hpp"


TX_NAMESPACE_BEGIN

RetCode VKSwapchain::recreateSwapchain(vk::raii::PhysicalDevice const& physical_device, vk::raii::Device const& device,
                                       const Window* window, const tx_vector<uint32_t>& queue_family_indices,
                                       vk::PresentModeKHR present_mode) {
    return RetCode::SUCCESS;
}

RetCode VKSwapchain::initSwapchain(vk::raii::PhysicalDevice const& physical_device, vk::raii::SurfaceKHR const& surface,
                                   vk::raii::Device const& device, const Window* window,
                                   const tx_vector<uint32_t>& queue_family_indices, vk::PresentModeKHR present_mode) {
    auto formats       = physical_device.getSurfaceFormatsKHR(*surface);
    auto present_modes = physical_device.getSurfacePresentModesKHR(*surface);

    TX_ASSERT(!formats.empty());

    if (formats.empty()) {
        ERROR_LOG("Cannot find any surface format.");
        return RetCode::VULKAN_SURFACE_FORMAT_EMPTY_ERROR;
    }
    if (present_modes.empty()) {
        ERROR_LOG("Cannot find any present mode.");
        return RetCode::VULKAN_SURFACE_FORMAT_EMPTY_ERROR;
    }

    swapchain_format = formats[0];
    for (auto const& format : formats) {
        if (vk::Format::eR8G8B8A8Srgb == format.format && vk::ColorSpaceKHR::eSrgbNonlinear == format.colorSpace) {
            swapchain_format = format;
            break;
        }

        if (vk::Format::eB8G8R8A8Srgb == format.format && vk::ColorSpaceKHR::eSrgbNonlinear == format.colorSpace) {
            swapchain_format = format;
            break;
        }
    }

    this->present_mode = present_mode;

    if (std::find(present_modes.begin(), present_modes.end(), vk::PresentModeKHR::eFifoRelaxed) !=
        present_modes.end()) {
        present_mode = vk::PresentModeKHR::eFifoRelaxed;
    }

    auto caps = physical_device.getSurfaceCapabilitiesKHR(*surface);

    uint32_t image_count{2};
    if (image_count < caps.minImageCount) {
        image_count = caps.minImageCount + 1;
    }
    if (caps.maxImageCount > 0 && image_count > caps.maxImageCount) {
        image_count = caps.maxImageCount;
    }

    extent = caps.currentExtent;
    if (std::numeric_limits<uint32_t>::max() == extent.width) {
        auto& window_info = window->window_info();
        extent.setWidth(window_info.width).setHeight(window_info.height);
    }

    vk::SwapchainCreateInfoKHR swapchain_info{};
    swapchain_info.setOldSwapchain(*swapchain)
            .setSurface(*surface)
            .setMinImageCount(image_count)
            .setImageFormat(swapchain_format.format)
            .setImageColorSpace(swapchain_format.colorSpace)
            .setImageExtent(extent)
            .setImageArrayLayers(1)
            .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
            .setPreTransform(caps.currentTransform)
            .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
            .setPresentMode(present_mode)
            .setClipped(VK_TRUE);

    if (queue_family_indices.size() < 2) {
        swapchain_info.setImageSharingMode(vk::SharingMode::eExclusive);
    } else {
        swapchain_info.setImageSharingMode(vk::SharingMode::eConcurrent).setQueueFamilyIndices(queue_family_indices);
    }

    auto res = device.createSwapchainKHR(swapchain_info);
    if (!res.has_value()) {
        return RetCode::VULKAN_SWAPCHAIN_CREATE_FAILED_ERROR;
    }
    swapchain = std::move(res.value());

    initSwapchainImagesAndViews(device);

    return RetCode::SUCCESS;
}

RetCode VKSwapchain::initSwapchainImagesAndViews(vk::raii::Device const& device) {
    TX_ASSERT(images.empty());
    TX_ASSERT(image_views.empty());

    auto swapchain_images = swapchain.getImages();
    images.reserve(swapchain_images.size());
    for (auto const& image : swapchain_images) {
        images.emplace_back(device, static_cast<VkImage>(image));
    }

    image_views.reserve(images.size());
    for (auto const& image : images) {
        vk::ImageViewCreateInfo create_info;
        create_info.setImage(*image)
                .setViewType(vk::ImageViewType::e2D)
                .setFormat(swapchain_format.format)
                .setComponents(vk::ComponentMapping{vk::ComponentSwizzle::eIdentity, vk::ComponentSwizzle::eIdentity,
                                                    vk::ComponentSwizzle::eIdentity, vk::ComponentSwizzle::eIdentity})
                .setSubresourceRange(vk::ImageSubresourceRange{vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});
        auto res = device.createImageView(create_info);
        if (!res.has_value()) {
            ERROR_LOG("Failed to create image view: {}", vk::to_string(res.error()));
            return RetCode::VULKAN_SWAPCHAIN_CREATE_FAILED_ERROR;
        }
        image_views.emplace_back(std::move(res.value()));
    }

    TX_ASSERT(image_views.size() == images.size());
    return RetCode::SUCCESS;
}

ResValT<VKSwapchain> VKSwapchain::createSwapchain(vk::raii::PhysicalDevice const& physical_device,
                                                  vk::raii::SurfaceKHR const& surface, vk::raii::Device const& device,
                                                  const Window* window, const tx_vector<uint32_t>& queue_family_indices,
                                                  vk::PresentModeKHR present_mode) {
    VKSwapchain swapchain;
    auto ret = swapchain.initSwapchain(physical_device, surface, device, window, queue_family_indices, present_mode);
    if (ret != RetCode::SUCCESS) {
        ERROR_LOG("Failed to create swapchain: {}", ret);
        return UNEXPECTED(ret);
    }
    return swapchain;
}

TX_NAMESPACE_END
