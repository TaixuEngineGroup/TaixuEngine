//
// Created by xmmmmmovo on 11/21/2023.
//

#pragma once

#include "taixu/common/base/macro.hpp"
#include "taixu/common/log/logger.hpp"

TX_NAMESPACE_BEGIN

/**
 * @brief
 *
 * @tparam RegisterKeyT
 * @tparam CreateFunctorT
 * @note This Return type must is pointer and CreateFunctor must invokable
 */
template<typename RegisterKeyT, typename ReturnT, typename CreateInfoT>
class AbstractFactory {
public:
    using RegisterKeyTTrait = RegisterKeyT;
    using CreateFunctorT    = std::function<ReturnT(CreateInfoT&&)>;
    using CreateInfoTTrait  = CreateInfoT;
    using ReturnTTrait      = ReturnT;

protected:
    TX_INLINE static std::unordered_map<RegisterKeyT, CreateFunctorT> creation_func_map{};

public:
    static bool registerCreationFunc(RegisterKeyT key, CreateFunctorT func) {
        TX_ASSERT_MSG(func, "func is nullptr");
        auto iter = creation_func_map.find(key);

        if (iter != creation_func_map.end()) {
            WARN_LOG("This _window have already registered");
            iter->second = std::move(func);
            return true;
        } else {
            creation_func_map.emplace(key, std::move(func));
            return true;
        }

        return false;
    }

    static ReturnT createProduct(RegisterKeyT  key,
                                 CreateInfoT&& args) {// NOLINT
        decltype(auto) iter = creation_func_map.find(key);

        if (creation_func_map.end() == iter) {
            FATAL_LOG("Cannot create the unsupported {}", typeid(RegisterKeyT).name());
            return nullptr;
        }
        return iter->second(std::forward<CreateInfoT>(args));
    }
};

#define TX_FACTORY_REGISTER(FACTORY_NAME, NAME, KEY_NAME, CREATE_FUNC_NAME)                                            \
    static const struct __register_##FACTORY_NAME##NAME {                                                              \
        __register_##FACTORY_NAME##NAME() {                                                                            \
            FACTORY_NAME::registerCreationFunc(KEY_NAME, CREATE_FUNC_NAME);                                            \
        }                                                                                                              \
    } __register_##FACTORY_NAME##NAME##_inst;

TX_NAMESPACE_END
