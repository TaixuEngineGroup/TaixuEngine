//
// Created by xmmmmmovo on 1/25/2024.
//

#pragma once

#include <cstdint>

#include "taixu/common/base/macro.hpp"

#include "common/hal/tx_string.hpp"

namespace taixu {

enum class EnumShaderStage : uint8_t {
    FRAGMENT,
    VERTEX,
    GEOMETRY,
    HULL,
    DOMAINS,
    COMPUTE,
};


struct TXShaderModuleCreateInfo {
    tx_string_view  name{};
    const uint32_t* binaries{nullptr};
    size_t          binaries_size{0};
};

class TXShaderModule {
    PROTOTYPE_ONLY_GETTER_VALPASS(protected, tx_string_view, name);

public:
    TXShaderModule(const TXShaderModule&)            = delete;
    TXShaderModule(TXShaderModule&&)                 = default;
    TXShaderModule& operator=(const TXShaderModule&) = delete;
    TXShaderModule& operator=(TXShaderModule&&)      = default;

    explicit TXShaderModule(TXShaderModuleCreateInfo const& info) : _name(info.name) {};
    virtual ~TXShaderModule() = default;
};

}// namespace taixu
