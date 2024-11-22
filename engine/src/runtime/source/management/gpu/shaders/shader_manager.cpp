//
// Created by xmmmmmovo on 1/28/2024.
//

#include "shader_manager.hpp"

namespace taixu {

void TXShaderModuleManager::init(pro::proxy<TXGfxProxy> const& gfx_proxy) {
    _gfx_proxy = gfx_proxy;
}

std::shared_ptr<TXShaderModule>
TXShaderModuleManager::createShaderModuleInner(TXShaderModuleCreateInfo const& info) const {
    return _gfx_proxy->createShaderModule(info);
}

std::shared_ptr<TXShaderModule>
TXShaderModuleManager::createCustomShaderModule(const TXShaderModuleCreateInfo& info) const {
    return createShaderModuleInner(info);
}

std::shared_ptr<TXShaderModule> TXShaderModuleManager::getBuiltinShaderModule(TXBuiltinShader builtin_shader) const {
    if (builtin_modules.at(static_cast<size_t>(builtin_shader)) == nullptr) {
        std::shared_ptr<TXShaderModule> module =
                createShaderModuleInner(builtin_shader_create_infos.at(static_cast<size_t>(builtin_shader)));
        builtin_modules.at(static_cast<size_t>(builtin_shader)) = module;
        return module;
    }
    return builtin_modules.at(static_cast<size_t>(builtin_shader));
}

}// namespace taixu
