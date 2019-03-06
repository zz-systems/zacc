//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2018 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------------

#pragma once
#include <array>
#include <zacc/util/type/type_traits.hpp>
#include <zacc/util/type/cast.hpp>

#include <zacc/util/macros.hpp>
#include <zacc/util/collections.hpp>

namespace zacc {

    template<typename T, typename enable = void>
    struct ztraits {
        /// vector size (1 - scalar, 4, 8, 16, ...)
        static constexpr size_t size = 1;

        /// capabilities
        static constexpr uint64_t feature_mask = 0;

        /// memory alignment
        static constexpr size_t alignment = 0;

        /// scalar type? vector type?
        static constexpr bool is_vector = false;

        /// vector type, like __m128i for sse 4x integer vector
        using vector_type = void;

        /// scalar type, like int for sse 4x integer vector
        using element_type = void;

        /// extracted std::array of (dim) scalar values
        using extracted_type = void;

        using zval_type = void;
        using bval_type = void;

        using tag = void;
    };

    // =================================================================================================================

    /// vector size (1 - scalar, 4, 8, 16, ...)
    template<typename T>
    constexpr size_t size_v = ztraits<T>::size;

    /// capabilities
    template<typename T>
    constexpr uint64_t feature_mask_v = ztraits<T>::feature_mask;

    /// memory alignment
    template<typename T>
    constexpr size_t alignment_v = ztraits<T>::alignment;

    /// scalar type? vector type?
    template<typename T>
    constexpr bool is_vector_v = ztraits<T>::is_vector;

    /// vector type, like __m128i for sse 4x integer vector
    template<typename T>
    using vector_t = typename ztraits<T>::vector_type;

    /// scalar type, like int for sse 4x integer vector
    template<typename T>
    using element_t = typename ztraits<T>::element_type;

    /// extracted std::array of (dim) scalar values
    template<typename T>
    using extracted_t = typename ztraits<T>::extracted_type;

    template<typename T>
    using zval_t = typename ztraits<T>::zval_type;
    template<typename T>
    using bval_t = typename ztraits<T>::bval_type;

    template<typename T>
    using tag_t = typename ztraits<T>::tag;

    // =================================================================================================================

    template<typename T>
    using is_zval = std::integral_constant<bool, std::is_same<tag_t<T>, zval_tag>::value && std::is_arithmetic<element_t<T>>::value>;

    template<typename T>
    using is_bval = std::integral_constant<bool, std::is_same<tag_t<T>, bval_tag>::value>;

    template<typename T>
    using is_cval = std::integral_constant<bool, std::is_same<tag_t<T>, cval_tag>::value && is_zval<element_t<T>>::value>;

    template<typename T>
    using is_integral = std::integral_constant<bool, std::is_integral<element_t<T>>::value>;

    template<typename T>
    using is_floating_point = std::integral_constant<bool, std::is_floating_point<element_t<T>>::value>;

    template<typename T>
    using is_float = std::integral_constant<bool, std::is_same<element_t<T>, float>::value>;

    template<typename T>
    using is_double = std::integral_constant<bool, std::is_same<element_t<T>, double>::value>;

    template<typename T>
    using is_scalar = std::integral_constant<bool, !is_vector_v<T>>;

    template<typename T>
    using is_vector = std::integral_constant<bool, is_vector_v<T>>;

    template<typename T>
    using storage_t = select_t<
            when<!is_vector_v<T> && is_bval<T>::value, bool>,
            when<!is_vector_v<T> && is_zval<T>::value, element_t<T>>,
            when< true /*is_vector_v<T>*/,             vector_t<T>>>;

    template<typename T>
    using view_t = select_t<
            when<is_bval<T>::value, std::array<bool, size_v<T>>>,
            when<is_zval<T>::value, std::array<element_t<T>, size_v<T>>>,
            when<is_cval<T>::value, std::array<element_t<T>, size_v<T>>>>;



}