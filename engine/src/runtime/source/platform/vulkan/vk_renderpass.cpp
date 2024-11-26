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
#include "taixu/common/log/logger.hpp"

TX_NAMESPACE_BEGIN

VKRenderPass VKRenderPass::createPresentRenderPass(vk::raii::Device const& device) noexcept {
    // Note: the stencilLoadOp & stencilStoreOp members are left initialized
    // to 0(= DONT CARE).The image format(R8G8B8A8 SRGB) of the color
    // attachment does not have a stencil component, so these are ignored either way.

    // logic: renderpass in -> subpasss[0] -> external renderpass output

    VKRenderPass render_pass{};

    std::array<vk::AttachmentDescription, 1> desc{};
    desc.at(0)
            .setFormat(vk::Format::eB8G8R8A8Srgb)
            .setSamples(vk::SampleCountFlagBits::e1)
            .setLoadOp(vk::AttachmentLoadOp::eClear)
            .setStoreOp(vk::AttachmentStoreOp::eStore)
            .setInitialLayout(vk::ImageLayout::eUndefined)
            .setFinalLayout(vk::ImageLayout::eTransferSrcOptimal);

    std::array<vk::AttachmentReference, 1> subpassrefs{};
    subpassrefs.at(0)
            .setAttachment(0)// zero is the index of attachment.
            .setLayout(vk::ImageLayout::eColorAttachmentOptimal);
    std::array<vk::SubpassDescription, 1> subpasses{};
    subpasses.at(0).setPipelineBindPoint(vk::PipelineBindPoint::eGraphics).setColorAttachments(subpassrefs);

    // This subpass only uses a single color attachment, and does not use any
    // other attachment types.We can therefore leave many of the members at
    // zero/nullptr.If this subpass used a depth attachment(= depth buffer),
    // we would specify this via the pDepthStencilAttachment member.

    // See the documentation for VkSubpassDescription for other attachment
    // types and the use/meaning of those.

    std::array<vk::SubpassDependency, 1> dependencies{};
    dependencies.at(0)
            .setDependencyFlags(vk::DependencyFlagBits::eByRegion)
            .setSrcSubpass(0)// subpass index
            .setSrcAccessMask(vk::AccessFlagBits::eColorAttachmentWrite)
            .setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput)
            .setDstSubpass(VK_SUBPASS_EXTERNAL)
            .setDstAccessMask(vk::AccessFlagBits::eTransferRead)
            .setDstStageMask(vk::PipelineStageFlagBits::eTransfer);

    vk::RenderPassCreateInfo create_info{};
    create_info.setAttachments(desc).setSubpasses(subpasses).setDependencies(dependencies);

    auto ret = device.createRenderPass(create_info);
    if (!ret.has_value()) {
        ERROR_LOG("Failed to create render pass: {}", vk::to_string(ret.error()));
        return {};
    }
    render_pass._render_pass = std::move(ret.value());

    return render_pass;
}

TX_NAMESPACE_END
