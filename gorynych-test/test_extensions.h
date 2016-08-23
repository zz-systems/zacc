//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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
#include <functional>
#include "../gorynych/gorynych.h"

namespace zzsystems { namespace gorynych { namespace test {

#if defined(COMPILE_OPENCL)

			using capability = capability_OPENCL;
#define TEST_PREFIX(test_name) test_name"- OpenCL"

#define CATCH_BRANCH_PREFIX AVX2_TEST_

#elif defined(COMPILE_AVX2)

			using capability = capability_AVX2;
#define TEST_PREFIX(test_name) test_name"- avx2"

#define CATCH_BRANCH_PREFIX AVX2_TEST_

#elif defined(COMPILE_AVX1)

			using capability = capability_AVX1;
#define TEST_PREFIX(test_name) test_name" - avx1"

#define CATCH_BRANCH_PREFIX AVX1_TEST_

#elif defined(COMPILE_SSE4FMA)

			using capability = capability_SSE4FMA;
#define TEST_PREFIX(test_name) test_name"- sse4 fma"

#define CATCH_BRANCH_PREFIX SSE4_FMA_TEST_

#elif defined(COMPILE_SSE4)

			using capability = capability_SSE4;
#define TEST_PREFIX(test_name) test_name"- sse4"

#define CATCH_BRANCH_PREFIX SSE4_TEST_

#elif defined(COMPILE_SSSE3)

			using capability = capability_SSSE3;
#define TEST_PREFIX(test_name) test_name"- ssse3"

#define CATCH_BRANCH_PREFIX SSSE3_TEST_

#elif defined(COMPILE_SSE3)

			using capability = capability_SSE3;
#define TEST_PREFIX(test_name) test_name"- sse3"

#define CATCH_BRANCH_PREFIX SSE3_TEST_

#elif defined(COMPILE_SSE2)

			using capability = capability_SSE2;
#define TEST_PREFIX(test_name) test_name"- sse2"

#define CATCH_BRANCH_PREFIX SSE2_TEST_

#else

			using capability = capability_FPU;
#define TEST_PREFIX(test_name) test_name"- x87"

#define CATCH_BRANCH_PREFIX X87_TEST_

#endif
}}}

//#define CATCH_CONFIG_COUNTER
#include "../Catch_Custom/single_include/catch.hpp"

namespace zzsystems { namespace gorynych { namespace test {

    using vreal = static_dispatcher<capability>::vreal;
    using vint  =  static_dispatcher<capability>::vint;

    using sint  = int;
    using sreal = float;
    template<typename vtype, typename stype>
    inline void test_validate(stype expected, const vtype &val) {
        ALIGNED stype tested[dim<vtype>()];

        extract(val, tested);

        for (size_t i = 0; i < dim<vtype>(); i++)
        {
            if(std::is_floating_point<stype>::value)
            {
                REQUIRE(expected == Approx(tested[i]));
            }
            else
            {
                REQUIRE(expected == tested[i]);
            }
        }
    };

    template<typename vtype, typename stype>
    inline void btest_validate(bool expected, const vtype &val) {
        ALIGNED stype tested[dim<vtype>()];

        extract(val, tested);

        for (size_t i = 0; i < dim<vtype>(); i++) {
            //INFO(" expected: " << expected);
            //INFO(" raw value is " << tested[i]);
            //INFO(" converted value is " << (*reinterpret_cast<int *>(&tested[i]) != 0x0));
            REQUIRE(expected == (*reinterpret_cast<stype *>(&tested[i]) != 0x0));
        }
    };

    template<typename vtype, typename stype>
    inline void test(stype a, stype b, std::function<stype(stype, stype)> scalar_op,
                     std::function<vtype(vtype, vtype)> vector_op) {
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

        stype expected = scalar_op(a, b);
        vtype val = vector_op(a, b);

        test_validate(expected, val);
    };

    template<typename vtype, typename stype>
    inline void test(std::function<stype(void)> scalar_op, std::function<vtype(void)> vector_op) {
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

        stype expected 	= scalar_op();
        vtype val 		= vector_op();

        test_validate(expected, val);
    };

    template<typename vtype, typename stype>
    inline void test(stype a, std::function<stype(stype)> scalar_op, std::function<vtype(vtype)> vector_op) {
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

        stype expected = scalar_op(a);
        vtype val = vector_op(a);

        test_validate(expected, val);
    };

    template<typename vtype, typename stype>
    inline void test(stype a, stype b, stype c, std::function<stype(stype, stype, stype)> scalar_op, std::function<vtype(vtype, vtype, vtype)> vector_op) {
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

        stype expected 	= scalar_op(a, b, c);
        vtype val 		= vector_op(a, b, c);

        test_validate(expected, val);
    };

    template<typename vtype, typename stype>
    inline void btest(stype a, stype b, std::function<bool(stype, stype)> scalar_op,
                      std::function<vtype(vtype, vtype)> vector_op) {
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

        bool expected = scalar_op(a, b);
        vtype val = vector_op(a, b);

        btest_validate<vtype, stype>(expected, val);
    };

    template<typename vtype, typename stype>
    inline void btest(stype a, std::function<bool(stype)> scalar_op, std::function<vtype(vtype)> vector_op) {
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

        bool expected = scalar_op(a);
        vtype val = vector_op(a);

        btest_validate<vtype, stype>(expected, val);
    };
}}}