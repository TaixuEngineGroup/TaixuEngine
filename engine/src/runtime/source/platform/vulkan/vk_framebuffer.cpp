/**
 * @file vk_framebuffer.cpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-24
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#include "vk_framebuffer.hpp"
#include "taixu/common/log/logger.hpp"

TX_NAMESPACE_BEGIN

ResValT<VKFramebuffer>
VKFramebuffer::createFramebuffer(vk::raii::Device const& device, vk::raii::RenderPass const& render_pass,
                                 vk::ArrayProxyNoTemporaries<const vk::ImageView> const& attachments, uint32_t width,
                                 uint32_t height) noexcept {
    vk::FramebufferCreateInfo create_info{};
    create_info.setRenderPass(*render_pass).setAttachments(attachments).setWidth(width).setHeight(height).setLayers(1);

    auto framebuffer = device.createFramebuffer(create_info);
    if (!framebuffer.has_value()) {
        ERROR_LOG("Failed to create framebuffer: {}", vk::to_string(framebuffer.error()));
        return UNEXPECTED(RetCode::VULKAN_FRAMEBUFFER_CREATE_FAILED_ERROR);
    }

    VKFramebuffer ret;
    ret._framebuffer = std::move(framebuffer.value());
    return ret;
}

TX_NAMESPACE_END
