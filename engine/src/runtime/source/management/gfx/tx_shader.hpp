//
// Created by xmmmmmovo on 1/25/2024.
//

#pragma once

#include <cstdint>

#include "taixu/common/base/macro.hpp"
#include "taixu/common/designs/noncopyable.hpp"

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

enum class EnumShaderSourceType : uint8_t { NONE = 0, GLSL, SPIRV, HLSL };

struct TXShaderModuleCreateInfo {
    tx_string_view       name{};
    const uint8_t*       binaries{nullptr};
    size_t               binaries_size{0};
    EnumShaderSourceType source_type{EnumShaderSourceType::NONE};
    EnumShaderStage      stage{};
};

class TXShaderModule {
    PROTOTYPE_ONLY_GETTER_VALPASS(protected, tx_string_view, name);
    PROTOTYPE_ONLY_GETTER_VALPASS(protected, EnumShaderStage, stage);

public:
    TXShaderModule(const TXShaderModule&)            = delete;
    TXShaderModule(TXShaderModule&&)                 = delete;
    TXShaderModule& operator=(const TXShaderModule&) = delete;
    TXShaderModule& operator=(TXShaderModule&&)      = delete;

    explicit TXShaderModule(TXShaderModuleCreateInfo const& info) : _name(info.name), _stage{info.stage} {};
    virtual ~TXShaderModule() = default;
};

}// namespace taixu
