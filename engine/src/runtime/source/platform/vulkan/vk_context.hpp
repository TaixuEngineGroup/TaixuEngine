/**
 * @file vk_context.hpp
 * @author xmmmmmovo
 * @date 2024-10-20
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "management/gfx/tx_context.hpp"
#include "taixu/common/base/macro.hpp"
#include "taixu/common/base/result.hpp"

#include "vk_surface.hpp"
TX_NAMESPACE_BEGIN

/**
 * @brief Vulkan Context, create resources or vk objects.
 *
 */
class VKContext final : private Noncopyable {
private:
    vk::raii::Instance               _instance{VK_NULL_HANDLE};
    vk::raii::DebugUtilsMessengerEXT _debug_messenger{VK_NULL_HANDLE};
    vk::raii::SurfaceKHR             _surface{VK_NULL_HANDLE};

    vk::raii::Device         _device{VK_NULL_HANDLE};
    vk::raii::PhysicalDevice _physical_device{VK_NULL_HANDLE};

    // We need one or two queues:
    // - best case: one GRAPHICS queue that can present
    // - otherwise: one GRAPHICS queue and any queue that can present
    std::uint32_t   _graphics_family_index{0};
    vk::raii::Queue _graphics_queue{VK_NULL_HANDLE};
    bool            _use_graphics_as_present{false};
    std::uint32_t   _present_family_index{0};
    vk::raii::Queue _present_queue{VK_NULL_HANDLE};

public:
    static ResValT<pro::proxy<TXGfxProxy>> createContext(const TXGfxCreateInfo& window_ctx);
};

TX_GFX_CONTEXT_FACTORY_REGISTER(VKContext,// NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
                                RenderAPI::VULKAN);

TX_NAMESPACE_END
