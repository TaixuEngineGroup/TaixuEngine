/**
 * @file function_utils.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-16
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include <memory>

TX_NAMESPACE_BEGIN

template<typename ReturnT, typename ConstructFunc, typename CreateInfoT>
class CreateFunctor {
public:
    using ReturnTTrait     = ReturnT;
    using CreateInfoTTrait = CreateInfoT;

    auto operator()(CreateInfoT&& args) const -> ReturnT {
        return ConstructFunc(std::forward<CreateInfoT>(args));
    }
};

template<typename ReturnT, typename CreateInfoT, typename PolymoT = ReturnT>
class CreateUniquePtrFunctor {
public:
    using ReturnTTrait     = ReturnT;
    using CreateInfoTTrait = CreateInfoT;
    using PolymoTTrait     = PolymoT;

    auto operator()(CreateInfoT&& args) const -> ReturnT {
        return std::make_unique<PolymoT>(std::forward<CreateInfoT>(args));
    }
};

template<typename ReturnT, typename CreateInfoT, typename PolymoT = ReturnT>
class CreateSharedPtrFunctor {
public:
    using ReturnTTrait     = ReturnT;
    using CreateInfoTTrait = CreateInfoT;
    using PolymoTTrait     = PolymoT;

    auto operator()(CreateInfoT&& args) const -> ReturnT {
        return std::make_shared<PolymoT>(std::forward<CreateInfoT>(args));
    }
};

template<typename ReturnT, typename ConstructWrapper, typename CreateInfoT>
class CreateWrapperFunctor {
public:
    using ReturnTTrait     = ReturnT;
    using CreateInfoTTrait = CreateInfoT;
    auto operator()(CreateInfoT&& args) const -> ReturnT {
        return ConstructWrapper()(std::forward<CreateInfoT>(args));
    }
};

TX_NAMESPACE_END
