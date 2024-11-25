/**
 * @file vk_pipeline.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-24
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */
#pragma once

#include "management/gfx/tx_pipeline.hpp"
#include "taixu/common/base/macro.hpp"


TX_NAMESPACE_BEGIN

class VKPipelineLayout : public TXPipelineLayout {
public:
    vk::raii::PipelineLayout pipeline_layout{VK_NULL_HANDLE};
};

class VKPipeline {
private:
    vk::raii::Pipeline _pipeline{VK_NULL_HANDLE};

public:
    [[nodiscard]] vk::raii::Pipeline const& getVKPipeline() const noexcept {
        return _pipeline;
    }

    /**
     * @brief Create a Quad Pipeline object, rendered by one triangle.
     *
     * @param device
     * @param render_pass
     * @return VKPipeline
     */
    static VKPipeline createQuadPipeline(vk::raii::Device const& device, vk::raii::RenderPass const& render_pass,
                                         vk::Extent2D const& extent, TXPipelineCreateInfo const& info) noexcept;
};

TX_NAMESPACE_END
