//
// Created by Sergej Zuyev on 12/12/2016.
//

#pragma once

#include <type_traits>
#include <tmmintrin.h>

namespace zacc {
    template<typename T>
    struct is_float32_vec : std::false_type {
    };
    template<>
    struct is_float32_vec<__m128> : std::true_type {
    };

    template<typename T>
    struct is_float64_vec : std::false_type {
    };
    template<>
    struct is_float64_vec<__m128d> : std::true_type {
    };

    template<typename T>
    struct is_int_vec : std::false_type {
    };
    template<>
    struct is_int_vec<__m128i> : std::true_type {
    };
}
