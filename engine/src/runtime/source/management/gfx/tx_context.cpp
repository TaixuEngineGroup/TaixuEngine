/**
 * @file tx_context.cpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "tx_context.hpp"

#include "common/log/custom_fmt.hpp"
#include "taixu/common/log/logger.hpp"
TX_NAMESPACE_BEGIN


pro::proxy<TXGfxProxy> create(const Window* window, RenderAPI api) {
    switch (api) {
        case RenderAPI::VULKAN: {
            auto res = VKContext::createVulkanContext(window);
            if (res.has_value()) {
                ERROR_LOG("Failed to create vulkan context: {}", res.error());
            }
            return std::move(res.value());
        } break;
        case RenderAPI::WGPU: {

        } break;
    }
}

TX_NAMESPACE_END
