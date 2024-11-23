//
// Created by xmmmmmovo on 1/28/2024.
//
#pragma once

#include "management/gfx/tx_context.hpp"
#include "management/gfx/tx_shader.hpp"
#include "taixu/common/base/hash.hpp"

#include <array>

#include <magic_enum/magic_enum.hpp>

namespace taixu {

enum class TXBuiltinShader : uint8_t {
    FORWARD_VERT = 0,
    FORWARD_FRAG = 1,
};

static constexpr std::size_t TX_BUILTIN_SHADER_SIZE = magic_enum::enum_count<TXBuiltinShader>();

using TXBuiltinShaderCreateInfoArrT = std::array<TXShaderModuleCreateInfo, TX_BUILTIN_SHADER_SIZE>;
using TXBuiltinShaderModulePtrArrT  = std::array<std::shared_ptr<TXShaderModule>, TX_BUILTIN_SHADER_SIZE>;


#define INIT_BUILTIN_SHADER_MODULE_CREATE_INFO(name_, binaries_ptr, infos)                                             \
    {                                                                                                                  \
        auto& info         = (infos).at(static_cast<size_t>(name_));                                                   \
        info.name          = magic_enum::enum_name(name_);                                                             \
        info.binaries      = binaries_ptr;                                                                             \
        info.binaries_size = sizeof(binaries_ptr) / sizeof((binaries_ptr)[0]);                                         \
    }

class TXShaderModuleManager final {
private:
    TX_INLINE static TXBuiltinShaderCreateInfoArrT builtin_shader_create_infos;
    TX_INLINE static TXBuiltinShaderModulePtrArrT  builtin_modules;

    std::unordered_map<hash32_t, std::shared_ptr<TXShaderModule>> _custom_modules;

    pro::proxy<TXGfxProxy> _gfx_proxy{};

    [[nodiscard]] std::shared_ptr<TXShaderModule> createShaderModuleInner(TXShaderModuleCreateInfo const& info) const;

public:
    void init(pro::proxy<TXGfxProxy> const& gfx_proxy);

    [[nodiscard]] std::shared_ptr<TXShaderModule> createCustomShaderModule(const TXShaderModuleCreateInfo& info) const;

    [[nodiscard]] std::shared_ptr<TXShaderModule> getBuiltinShaderModule(TXBuiltinShader builtin_shader) const;
};


}// namespace taixu
