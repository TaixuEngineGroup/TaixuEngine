/**
 * @file container_tests.cpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-27
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */
#include "catch2/catch_test_macros.hpp"

#include "common/container/ring_buffer.hpp"

namespace {

using namespace taixu;

TEST_CASE("ring buffer test", "[container tests]") {
    RingBuffer<std::shared_ptr<int>> rb{100};
    rb.push(std::make_shared<int>(1));
    auto a = rb.pop();
    REQUIRE(1 == *a->get());
}

}// namespace
