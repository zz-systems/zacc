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
#include "stdafx.h"
#include "CppUnitTest.h"
#include <random>

#include "../gorynych/gorynych.h"
#include "../gorynych/unit_test_ext.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace zzsystems { namespace gorynych { namespace tests {
			
#define INIT_BIN_TEST_REAL \
	float ref_result[8];\
	sse_real\
		sse_lo1((_fref1)),\
		sse_hi1((_fref1 + 4)),\
		sse_lo2((_fref2)),\
		sse_hi2((_fref2 + 4)),\
		sse_result_lo, sse_result_hi;\
	avx_real \
		avx1((_fref1)),\
		avx2((_fref2)),\
		avx_result

#define INIT_BIN_TEST_INT \
	int ref_result[8];\
	sse_int\
		sse_lo1((_fref1)),\
		sse_hi1((_fref1 + 4)),\
		sse_lo2((_fref2)),\
		sse_hi2((_fref2 + 4)),\
		sse_result_lo, sse_result_hi;\
	avx_int \
		avx1((_fref1)),\
		avx2((_fref2)),\
		avx_result

#define CALC_BIN_TEST(op) \
	for (int i = 0; i < 8; i++) \
	{ ref_result[i] = _fref1[i] op _fref2[i]; }\
	sse_result_lo = sse_lo1 op sse_lo2; \
	sse_result_hi = sse_hi1 op sse_hi2; \
	avx_result = avx1 op avx2 

#define MAP_CMP_TO_1_AND_0_REAL \
	for (int i = 0; i < 8; i++) \
	{ ref_result[i] = ref_result[i] != 0.0f ? 1.0f : 0.0f; }\
	sse_result_lo = _mm_and_ps(_mm_cmpneq_ps(sse_result_lo.val, _mm_set1_ps(0.0f)), _mm_set1_ps(1.0f)); \
	sse_result_hi = _mm_and_ps(_mm_cmpneq_ps(sse_result_hi.val, _mm_set1_ps(0.0f)), _mm_set1_ps(1.0f)); \
	avx_result = _mm256_and_ps(_mm256_cmp_ps(avx_result.val, _mm256_set1_ps(0.0f), _CMP_NEQ_UQ), _mm256_set1_ps(1.0f)) 

#define VALIDATE_TEST_REAL \
	do { \
	ALIGN(16) float sse_r_lo[4], sse_r_hi[4], avx_r[8];\
	_mm_store_ps(sse_r_lo, sse_result_lo.val);\
	_mm_store_ps(sse_r_hi, sse_result_hi.val);\
	_mm256_store_ps(avx_r, avx_result.val);\
	for (int i = 0; i < 8; i++)\
	{\
		float ref_val = ref_result[i];\
		float sse_val = i < 4 ? sse_r_lo[i] : sse_r_hi[i - 4];\
		float avx_val = avx_r[i];\
		Assert::AreEqual(ref_val, sse_val, numeric_limits<float>::epsilon(), L"Mismatch between fpu and sse value");\
		Assert::AreEqual(ref_val, avx_val, numeric_limits<float>::epsilon(), L"Mismatch between fpu and avx value");\
		Assert::AreEqual(sse_val, avx_val, numeric_limits<float>::epsilon(), L"Mismatch between sse and avx value");\
	} \
	} \
	while(false)


			TEST_CLASS(TestOperations)
			{
			public:

				TEST_CLASS_INITIALIZE(Init_RefValues)
				{
					random_device rd;

					mt19937 e2(rd());

					uniform_real_distribution<float> rng(-225, 225);

					uniform_int_distribution<int> maskrng(0, 1);

					for (int i = 0; i < 8; i++)
					{
						_fref1[i] = static_cast<float>(rng(e2));
						_fref2[i] = static_cast<float>(rng(e2));
						_fref3[i] = static_cast<float>(rng(e2));

						_fmask[i] = (_bmask[i] = (maskrng(e2) > 0))
							? -numeric_limits<float>::quiet_NaN() // 0xFFFF'FFFF
							: 0.0f;

						/*_fmask[i] = (_bmask[i] = i % 2 == 0)
						? 1.0f : 0.0f;*/
					}

					//_mm256_store_ps(_fmask, _mm256_cmp_ps(_mm256_load_ps(_fmask), _mm256_set1_ps(0.0f), _CMP_GT_OS));
				}

				TEST_METHOD(Test_Add)
				{
					INIT_BIN_TEST_REAL;
					CALC_BIN_TEST(+);
					VALIDATE_TEST_REAL;
				}

				TEST_METHOD(Test_Sub)
				{
					INIT_BIN_TEST_REAL;
					CALC_BIN_TEST(-);
					VALIDATE_TEST_REAL;
				}

				TEST_METHOD(Test_Mul)
				{
					INIT_BIN_TEST_REAL;
					CALC_BIN_TEST(*);
					VALIDATE_TEST_REAL;
				}

				TEST_METHOD(Test_Div)
				{
					INIT_BIN_TEST_REAL;
					CALC_BIN_TEST(/ );
					VALIDATE_TEST_REAL;
				}

				TEST_METHOD(Test_GT)
				{
					INIT_BIN_TEST_REAL;
					CALC_BIN_TEST(>);
					MAP_CMP_TO_1_AND_0_REAL;
					VALIDATE_TEST_REAL;
				}

				TEST_METHOD(Test_LT)
				{
					INIT_BIN_TEST_REAL;
					CALC_BIN_TEST(<);
					MAP_CMP_TO_1_AND_0_REAL;
					VALIDATE_TEST_REAL;
				}

				TEST_METHOD(Test_EQ)
				{
					INIT_BIN_TEST_REAL;
					CALC_BIN_TEST(== );
					MAP_CMP_TO_1_AND_0_REAL;
					VALIDATE_TEST_REAL;
				}

				TEST_METHOD(Test_AND)
				{
					INIT_BIN_TEST_REAL;
					CALC_BIN_TEST(&&);
					MAP_CMP_TO_1_AND_0_REAL;
					VALIDATE_TEST_REAL;
				}

				TEST_METHOD(Test_OR)
				{
					INIT_BIN_TEST_REAL;
					CALC_BIN_TEST(|| );
					MAP_CMP_TO_1_AND_0_REAL;
					VALIDATE_TEST_REAL;
				}

				TEST_METHOD(Test_VSel)
				{
					INIT_BIN_TEST_REAL;

					for (int i = 0; i < 8; i++)
					{
						ref_result[i] = vsel(_bmask[i], _fref1[i], _fref2[i]);
					}

					sse_result_lo	= vsel(sse_real(_fmask), sse_lo1, sse_lo2);
					sse_result_hi	= vsel(sse_real(_fmask + 4), sse_hi1, sse_hi2);
					avx_result		= vsel(avx_real(_fmask), avx1, avx2);

					VALIDATE_TEST_REAL;
				}

				TEST_METHOD(Test_VMin)
				{
					INIT_BIN_TEST_REAL;

					for (int i = 0; i < 8; i++)
					{
						ref_result[i] = vmin(_fref1[i], _fref2[i]);
					}

					sse_result_lo = vmin(sse_lo1, sse_lo2);
					sse_result_hi = vmin(sse_hi1, sse_hi2);
					avx_result = vmin(avx1, avx2);

					VALIDATE_TEST_REAL;
				}

				TEST_METHOD(Test_VMax)
				{
					INIT_BIN_TEST_REAL;

					for (int i = 0; i < 8; i++)
					{
						ref_result[i] = vmax(_fref1[i], _fref2[i]);
					}

					sse_result_lo = vmax(sse_lo1, sse_lo2);
					sse_result_hi = vmax(sse_hi1, sse_hi2);
					avx_result = vmax(avx1, avx2);

					VALIDATE_TEST_REAL;
				}

			private:
				static float __declspec(align(16))  _fref1[8];
				static float __declspec(align(16))  _fref2[8];
				static float __declspec(align(16))  _fref3[8];
				static float __declspec(align(16))  _fmask[8];
				static bool _bmask[8];
			};

			float TestOperations::_fref1[8],
				TestOperations::_fref2[8],
				TestOperations::_fref3[8],
				TestOperations::_fmask[8];

			bool TestOperations::_bmask[8];
		}
	}
}