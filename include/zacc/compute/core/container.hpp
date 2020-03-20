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

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename T, size_t Size = 0>
    struct container {
        using type = std::array<T, Size>;
    };

    template<typename T, size_t Size = 0>
    using container_t = typename container<T, Size>::type;

    template<typename T>
    struct container<T, 0> {
        using type = std::vector<T>;
    };

    // =================================================================================================================

//#if defined(ZACC_SCALAR)

    // =================================================================================================================
    template<typename T>
    struct container<T, 1> {
        using type = std::array<T, 1>;//T;
    };

//    template<>
//    struct container<int8_t , 16> {
//        using type = __m128i;
//    };
//
//    template<>
//    struct container<int16_t, 8> {
//        using type = __m128i;
//    };
//
//    template<>
//    struct container<int32_t , 4> {
//        using type = __m128i;
//    };
//
//    template<>
//    struct container<int64_t, 2> {
//        using type = __m128i;
//    };
//
//    template<>
//    struct container<float, 4> {
//        using type = __m128;
//    };
//
//    template<>
//    struct container<double, 2> {
//        using type = __m128d;
//    };

    // =================================================================================================================

//#endif

#if defined(ZACC_SSE)

#include <zacc/backend/intrin.hpp>

        namespace zacc {

        //    template<typename Target>
        //    struct container<std::enable_if_t<Target::value & feature::sse2(), char>, Target, 16>
        //    {
        //        using type = __m128i;
        //    };
        //
        //    template<typename Target>
        //    struct container<std::enable_if_t<Target::value & feature::sse2(), short>, Target, 8>
        //    {
        //        using type = __m128i;
        //    };
        //
        //    template<typename Target>
        //    struct container<std::enable_if_t<Target::value & feature::sse2(), int>, Target, 4>
        //    {
        //        using type = __m128i;
        //    };
        //
        //    template<typename Target>
        //    struct container<std::enable_if_t<Target::value & feature::sse2(), float>, Target, 4>
        //    {
        //        using type = __m128;
        //    };
        //
        //    template<typename Target>
        //    struct container<std::enable_if_t<Target::value & feature::sse2(), double>, Target, 2>
        //    {
        //        using type = __m128d;
        //    };
        }

#endif

}}