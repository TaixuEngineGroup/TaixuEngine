/**
 * @file tx_context.hpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <proxy.h>

#include "common/log/custom_fmt.hpp"
#include "taixu/common/designs/abstract_factory.hpp"
#include "taixu/gameplay/gui/window.hpp"
#include "tx_shader.hpp"

TX_NAMESPACE_BEGIN

/**
 * @brief Imgui init function
 *
 */
PRO_DEF_MEM_DISPATCH(ImguiInitImpl, imguiInit);
/**
 * @brief Shader create function
 *
 */
PRO_DEF_MEM_DISPATCH(CreateShaderModuleImpl, createShaderModule);

/**
 * @brief Graphics proxy
 *
 */
struct TXGfxProxy
    : pro::facade_builder::add_convention<CreateShaderModuleImpl,
                                          std::shared_ptr<TXShaderModule>(TXShaderModuleCreateInfo const&)
                                                  const>::support_copy<pro::constraint_level::nontrivial>::build {};

struct TXGfxCreateInfo {
    const Window* window{nullptr};
};

class TXGFXContextFactory final : public AbstractFactory<RenderAPI, pro::proxy<TXGfxProxy>, TXGfxCreateInfo> {};

#define TX_GFX_CONTEXT_FACTORY_REGISTER(PRODUCT_CLASS_NAME, RENDER_API)                                                \
    static TXGFXContextFactory::ReturnTTrait __createFuncTXGFXContextFactory##PRODUCT_CLASS_NAME(                      \
            TXGFXContextFactory::CreateInfoTTrait&& info) {                                                            \
        auto res = PRODUCT_CLASS_NAME::createContext(std::forward<TXGFXContextFactory::CreateInfoTTrait>(info));       \
        if (!res.has_value()) {                                                                                        \
            ERROR_LOG("Failed to create vulkan context: {}", res.error());                                             \
            return nullptr;                                                                                            \
        }                                                                                                              \
        return std::move(res.value());                                                                                 \
    }                                                                                                                  \
    TX_FACTORY_REGISTER(TXGFXContextFactory, PRODUCT_CLASS_NAME, RENDER_API,                                           \
                        __createFuncTXGFXContextFactory##PRODUCT_CLASS_NAME)

TX_NAMESPACE_END
