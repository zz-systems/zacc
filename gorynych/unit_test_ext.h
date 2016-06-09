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

// Extensions for Microsoft unit testing framework.


#if defined (_MSC_VER) && defined(MS_CPP_UNITTESTFRAMEWORK) 
	#define INTERNALS_VISIBLE_TO_TEST(class_name) friend class class_name
#else
	#define INTERNALS_VISIBLE_TO_TEST(class_name) {}
#endif

#if defined (_MSC_VER) && defined(MS_CPP_UNITTESTFRAMEWORK)

#include "gorynych.h"
#include <type_traits>

namespace zzsystems { namespace gorynych { namespace tests {

	using capability_avx		= integral_constant<int, CAPABILITY_AVX1 | CAPABILITY_AVX2 >;
	using capability_sse4fma	= integral_constant<int, CAPABILITY_SSE2 | CAPABILITY_SSE3 | CAPABILITY_SSE41 | CAPABILITY_FMA3>;
	using capability_sse4		= integral_constant<int, CAPABILITY_SSE2 | CAPABILITY_SSE3 | CAPABILITY_SSE41>;
	using capability_sse		= integral_constant<int, CAPABILITY_SSE2 | CAPABILITY_SSE3>;
	using capability_fpu		= integral_constant<int, CAPABILITY_NONE>;

	using sse_real = static_dispatcher<capability_sse4fma>::vreal;
	using sse_int = static_dispatcher<capability_sse4fma>::vint;
	using avx_real = static_dispatcher<capability_avx>::vreal;
	using avx_int = static_dispatcher<capability_avx>::vint;

	template<typename TScalar>
	inline void AreEqual(const TScalar &expected, TScalar &tested)
	{
		Assert::AreEqual(expected, tested, 0.001f);
	}

	template<typename TVec>
	inline void AreEqual(const int &expected, const TVec &tested, const wchar_t* message = NULL)
	{
		auto word = sizeof(TVec) >> 2;
		remove_const_t<TVec>  e = tested;
		auto extracted = extract(e);

		for (int i = 0; i < word; i++)
		{
			Assert::AreEqual(expected, extracted[i], message);
		}
	}

	template<typename TVec>
	inline void AreEqual(const float &expected, const TVec &tested, const wchar_t* message = NULL)
	{
		auto word = sizeof(TVec) >> 2;

		remove_const_t<TVec> e = tested;

		auto extracted = extract(e);

		for (int i = 0; i < word; i++)
		{
			Assert::AreEqual(expected, extracted[i], 0.001f, message);
		}
	}

	template<typename TScalar, typename TVec>
	inline void AreEqual_NOE(const TScalar &expected, const TVec &tested)
	{
		auto word = sizeof(TVec) >> 2;

		remove_const_t<TVec> e = tested;
		auto extracted = extract(e);

		for (int i = 0; i < word; i++)
		{
			Assert::AreEqual(expected, extracted[i]);
		}
	}
}}}

#else
#include "../../Catch/single_include/catch.hpp"
#include "gorynych.h"

namespace zzsystems { namespace gorynych { namespace test {
			template<typename vtype, typename stype>
			inline void test_validate(stype expected, const vtype &val) {
				SIMD_ALIGN stype tested[dim<vtype>()];

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
				SIMD_ALIGN stype tested[dim<vtype>()];

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
#endif
