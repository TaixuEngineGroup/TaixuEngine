/**
 * @file window_factory.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-09-16
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "taixu/common/designs/abstract_factory.hpp"
#include "taixu/gameplay/gui/window.hpp"

TX_NAMESPACE_BEGIN

class WindowFactory : public AbstractFactory<WindowAPI, std::unique_ptr<Window>, WindowInfo> {};

#define TX_WINDOW_FACTORY_REGISTER(PRODUCT_CLASS_NAME, WINDOW_API)                                                     \
    static WindowFactory::ReturnTTrait __createFuncWindowFactory##PRODUCT_CLASS_NAME(                                  \
            WindowFactory::CreateInfoTTrait&& info) {                                                                  \
        return std::make_unique<PRODUCT_CLASS_NAME>(std::forward<WindowFactory::CreateInfoTTrait>(info));              \
    }                                                                                                                  \
    TX_FACTORY_REGISTER(WindowFactory, PRODUCT_CLASS_NAME, WINDOW_API, __createFuncWindowFactory##PRODUCT_CLASS_NAME)

TX_NAMESPACE_END
