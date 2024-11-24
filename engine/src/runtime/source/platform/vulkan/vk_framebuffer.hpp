/**
 * @file vk_framebuffer.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-24
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */
#pragma once

#include "common/hal/tx_container.hpp"
#include "taixu/common/base/macro.hpp"
#include "taixu/common/base/result.hpp"

TX_NAMESPACE_BEGIN

class VKFramebuffer {
private:
    vk::raii::Framebuffer          _framebuffer{VK_NULL_HANDLE};
    tx_vector<vk::raii::Image>     _color_images;
    tx_vector<vk::raii::ImageView> _color_image_views;

public:
    [[nodiscard]] vk::raii::Framebuffer const& getVKFramebuffer() const noexcept {
        return _framebuffer;
    }

    static ResValT<VKFramebuffer> createFramebuffer(vk::raii::Device const&                                 device,
                                                    vk::raii::RenderPass const&                             render_pass,
                                                    vk::ArrayProxyNoTemporaries<const vk::ImageView> const& attachments,
                                                    uint32_t width, uint32_t height) noexcept;
};

TX_NAMESPACE_END
