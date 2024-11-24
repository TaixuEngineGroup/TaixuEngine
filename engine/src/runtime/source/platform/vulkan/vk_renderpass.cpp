/**
 * @file vk_renderpass.cpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-24
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */
#include "vk_renderpass.hpp"

TX_NAMESPACE_BEGIN

ResValT<VKRenderPass> createMinimalRenderPass() {

    return VKRenderPass{};
}


TX_NAMESPACE_END
