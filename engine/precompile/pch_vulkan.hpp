//
// Created by xmmmmmovo on 1/6/2024.
//

#ifndef ENGINE_PRECOMPILE_PCH_VULKAN_CD66C63DA4B64D3BBA17477BBEAABFC2
#define ENGINE_PRECOMPILE_PCH_VULKAN_CD66C63DA4B64D3BBA17477BBEAABFC2

#define USE_VULKAN

#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#define VULKAN_HPP_NO_EXCEPTIONS
#define VULKAN_HPP_RAII_NO_EXCEPTIONS

#include <vulkan/vulkan_hpp_macros.hpp>
#include <vulkan/vulkan_raii.hpp>

#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1
#include <vk_mem_alloc.h>

#endif// ENGINE_PRECOMPILE_PCH_VULKAN_CD66C63DA4B64D3BBA17477BBEAABFC2
