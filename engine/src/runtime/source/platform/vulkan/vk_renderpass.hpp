/**
 * @file vk_renderpass.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-23
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */
#pragma once

#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN

class VKRenderPass {
    vk::raii::RenderPass _render_pass{VK_NULL_HANDLE};
};

TX_NAMESPACE_END
