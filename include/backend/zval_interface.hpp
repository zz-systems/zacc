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
namespace zacc
{
    struct zval_tag {};
    struct bval_tag {};
    struct cval_tag {};


    template<typename Tag, typename Vector, typename MaskVector, typename Element, /*typename Tag,*/ size_t Size, size_t Alignment, uint64_t FeatureMask = 0xFFFF'FFFF'FFFF'FFFF>
    struct ztype
    {
        /// type tag
        using tag = Tag;

        /// vector size (1 - scalar, 4, 8, 16, ...)
        static constexpr size_t size = Size;

        /// memory alignment
        static constexpr size_t alignment = Alignment;

        /// feature mask (indicates available features)
        static constexpr uint64_t feature_mask = FeatureMask;

        /// scalar type? vector type?
        static constexpr bool is_vector = size > 1;

        /// vector type, like __m128i for sse 4x integer vector
        using vector_type = Vector;

        /// scalar type, like int for sse 4x integer vector
        using element_type = Element;

        /// mask type for boolean operations
        using mask_vector_type = MaskVector;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;
    };

#define USING_ZTYPE(Interface) \
    using Interface::size; \
    using Interface::alignment; \
    using Interface::feature_mask; \
    using Interface::is_vector; \
    using typename Interface::tag; \
    using typename Interface::element_type; \
    using typename Interface::vector_type; \
    using typename Interface::mask_vector_type; \
    using typename Interface::extracted_type

//#define USING_ZTYPE(Tag) \
//    using ztype<Vector, MaskVector, Element, Tag, Size, Alignment, FeatureMask>::tag; \
//    using ztype<Vector, MaskVector, Element, Tag, Size, Alignment, FeatureMask>::element_type; \
//    using ztype<Vector, MaskVector, Element, Tag, Size, Alignment, FeatureMask>::vector_type; \
//    using ztype<Vector, MaskVector, Element, Tag, Size, Alignment, FeatureMask>::mask_vector_type; \
//    using ztype<Vector, MaskVector, Element, Tag, Size, Alignment, FeatureMask>::extracted_type
}