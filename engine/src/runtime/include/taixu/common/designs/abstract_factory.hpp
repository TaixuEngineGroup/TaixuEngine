//
// Created by xmmmmmovo on 11/21/2023.
//

#pragma once

#include "taixu/common/base/macro.hpp"
#include "taixu/common/log/logger.hpp"

#include <iostream>

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
    TX_INLINE static std::unique_ptr<std::unordered_map<RegisterKeyT, CreateFunctorT>> creation_func_map{};

public:
    static bool registerCreationFunc(RegisterKeyT key, CreateFunctorT func) {
        TX_ASSERT_MSG(func, "func is nullptr");
        if (creation_func_map == nullptr) {
            creation_func_map = std::make_unique<std::unordered_map<RegisterKeyT, CreateFunctorT>>();
        }

        auto iter = creation_func_map->find(key);

        if (iter != creation_func_map->end()) {
            std::cout << fmt::format("This {} have already registered.\n", typeid(RegisterKeyT).name());
            return true;
        } else {
            creation_func_map->emplace(key, std::move(func));
            return true;
        }

        return false;
    }

    static ReturnT createProduct(RegisterKeyT  key,
                                 CreateInfoT&& args) {// NOLINT
        if (creation_func_map == nullptr) {
            std::cerr << "You need to register the creation function first.\n";
            return nullptr;
        }

        decltype(auto) iter = creation_func_map->find(key);
        if (creation_func_map->end() == iter) {
            std::cerr << fmt::format("Cannot create the unsupported {}.\n", typeid(RegisterKeyT).name());
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
