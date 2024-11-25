/**
 * @file tx_pipeline.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-25
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "common/hal/tx_container.hpp"
#include "management/gfx/tx_shader.hpp"
#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN

struct TXShaderDescriptor {
    std::shared_ptr<TXShaderModule> shader_module{};
    EnumShaderStage                 stage{};
};

class TXPipelineLayout {};

struct TXPipelineCreateInfo {
    tx_vector<TXShaderDescriptor>     shaders;
    std::shared_ptr<TXPipelineLayout> pipeline_layout{};
};

TX_NAMESPACE_END
