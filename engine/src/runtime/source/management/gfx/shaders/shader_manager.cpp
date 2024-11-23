//
// Created by xmmmmmovo on 1/28/2024.
//

#include "shader_manager.hpp"

#include "intern/shader_inc_list.hpp"

namespace taixu {
// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
#define SHADER_MODULE_CREATE_INFO_INIT(name_, binaries_ptr)                                                            \
    TXShaderModuleCreateInfo {                                                                                         \
        .name = (name_), .binaries = (reinterpret_cast<const uint32_t*>(binaries_ptr)),                                \
        .binaries_size = sizeof(binaries_ptr) / sizeof((binaries_ptr)[0])                                              \
    }

constexpr TXShaderModuleCreateInfo mappingBuiltinShader2CreateInfo(TXBuiltinShader builtin_shader) {
    switch (builtin_shader) {
        case TXBuiltinShader::FORWARD_VERT: {
            return SHADER_MODULE_CREATE_INFO_INIT("forward_vert", TRIANGLE_VERT);
        } break;
        case TXBuiltinShader::FORWARD_FRAG: {
            return SHADER_MODULE_CREATE_INFO_INIT("forward_frag", TRIANGLE_FRAG);
        } break;
    }
    return {};
}
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
void TXShaderModuleManager::init(pro::proxy<TXGfxProxy> const& gfx_proxy) {
    _gfx_proxy = gfx_proxy;
}

std::shared_ptr<TXShaderModule>
TXShaderModuleManager::createShaderModuleInner(TXShaderModuleCreateInfo const& info) const {
    INFO_LOG("Creating shader module: {}", info.name);
    return _gfx_proxy->createShaderModule(info);
}

std::shared_ptr<TXShaderModule>
TXShaderModuleManager::createCustomShaderModule(const TXShaderModuleCreateInfo& info) const {
    return createShaderModuleInner(info);
}

std::shared_ptr<TXShaderModule> TXShaderModuleManager::getBuiltinShaderModule(TXBuiltinShader builtin_shader) const {
    if (builtin_modules.at(static_cast<size_t>(builtin_shader)) == nullptr) {
        auto& cfref                            = builtin_shader_create_infos.at(static_cast<size_t>(builtin_shader));
        cfref                                  = mappingBuiltinShader2CreateInfo(builtin_shader);
        std::shared_ptr<TXShaderModule> module = createShaderModuleInner(cfref);
        builtin_modules.at(static_cast<size_t>(builtin_shader)) = module;
        return module;
    }
    return builtin_modules.at(static_cast<size_t>(builtin_shader));
}

}// namespace taixu
