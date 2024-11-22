/**
 * @file vk_shader.cpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-23
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#include "vk_shader.hpp"

TX_NAMESPACE_BEGIN

std::shared_ptr<TXShaderModule> VKShaderMod::createVKShaderModule(TXShaderModuleCreateInfo const& info) {
    std::shared_ptr<TXShaderModule> shader_module = std::make_shared<VKShaderMod>(info);

    vk::ShaderModuleCreateInfo create_info;
    create_info.setPCode(reinterpret_cast<const uint32_t*>(info.binaries)).setCodeSize(info.binaries_size);// NOLINT

    return nullptr;
}

TX_NAMESPACE_END
