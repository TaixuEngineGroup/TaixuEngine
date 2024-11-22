/**
 * @file vk_shader.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-22
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "management/gfx/tx_shader.hpp"
#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN

class VKShaderMod : public TXShaderModule {
private:
    vk::raii::ShaderModule _shader_module{VK_NULL_HANDLE};

public:
    static std::shared_ptr<TXShaderModule> createVKShaderModule(TXShaderModuleCreateInfo const& info);
};

TX_NAMESPACE_END
