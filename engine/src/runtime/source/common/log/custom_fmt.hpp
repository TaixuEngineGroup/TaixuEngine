/**
 * @file custom_fmt.hpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-10-20
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include <fmt/chrono.h>
#include <fmt/compile.h>
#include <fmt/core.h>
#include <fmt/std.h>
#include <magic_enum/magic_enum.hpp>

#include "common/utils/type_utils.hpp"
#include "taixu/common/base/core.hpp"

template<>
struct magic_enum::customize::enum_range<taixu::RetCode> {
    static constexpr int min = 0;      // NOLINT
    static constexpr int max = 1 << 10;// NOLINT
};

template<typename T>
concept FmtStringLikeT = std::is_same_v<std::decay_t<T>, fmt::basic_string_view<typename T::value_type>>;

// Generic fmt::formatter for any enum
template<typename T>
    requires std::is_enum_v<T>
struct fmt::formatter<T> {
    constexpr auto parse(fmt::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template<typename FormatContext>
    auto format(const T value, FormatContext& ctx) -> decltype(ctx.out()) {
        // Use magic_enum to convert enum to string
        auto name = magic_enum::enum_name(value);
        return fmt::format_to(ctx.out(), "{}", name.empty() ? "Unknown Enum" : name);
    }
};

// Generic fmt::formatter for any iterable
template<typename T>
    requires taixu::IterableT<T> && (!taixu::StringLikeT<T>) && (!FmtStringLikeT<T>)
struct fmt::formatter<T> {
    constexpr auto parse(fmt::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template<typename FormatContext>
    auto format(const T& container, FormatContext& ctx) -> decltype(ctx.out()) {
        auto it  = std::begin(container);
        auto end = std::end(container);

        fmt::format_to(ctx.out(), "[");// Begin with an opening bracket

        if (it != end) {
            fmt::format_to(ctx.out(), "{}", *it);// Print the first element
            ++it;
        }

        // Iterate over remaining elements and format them
        for (; it != end; ++it) {
            fmt::format_to(ctx.out(), ", {}", *it);
        }

        return fmt::format_to(ctx.out(), "]");// Close with a bracket
    }
};

// Specialization of fmt::formatter for associative containers (e.g., std::map)
template<typename T>
    requires taixu::KeyValueContainerT<T>
struct fmt::formatter<T> {
    constexpr auto parse(fmt::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const T& map, FormatContext& ctx) -> decltype(ctx.out()) {
        fmt::format_to(ctx.out(), "{{");
        auto it  = map.begin();
        auto end = map.end();
        if (it != end) {
            fmt::format_to(ctx.out(), "{}: {}", it->first, it->second);
            ++it;
        }
        for (; it != end; ++it) {
            fmt::format_to(ctx.out(), ", {}: {}", it->first, it->second);
        }
        return fmt::format_to(ctx.out(), "}}");
    }
};
