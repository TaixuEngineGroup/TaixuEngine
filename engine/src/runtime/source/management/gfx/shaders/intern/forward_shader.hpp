//
// Created by xmmmmmovo on 1/28/2024.
//
#pragma once

#ifdef USE_VULKAN
    #include "triangle_frag_vk.h"
    #include "triangle_vert_vk.h"

    #define TRIANGLE_FRAG TRIANGLE_FRAG_VK
    #define TRIANGLE_VERT TRIANGLE_VERT_VK
#endif
