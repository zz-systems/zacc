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

#include "../gorynych/gorynych.h"
#include "../gorynych/unit_test_ext.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//AreEqual(static_cast<float>	(expected), cfl<float>::name(),	L"scalar float invalid"); 
//AreEqual(static_cast<int32>	(expected), cfl<int32>::name(),		L"scalar int invalid"); 


namespace zzsystems { namespace gorynych { namespace tests {

#define VALIDATE_FASTLOAD_VALUE(name, expected) \
	AreEqual(static_cast<float>	(expected), cfl<float>::name(),	L"scalar float invalid");\
	AreEqual(static_cast<int>	(expected), cfl<int>::name(),      L"scalar int invalid");\
	AreEqual(static_cast<float>	(expected), cfl<sse_real>::name(), L"sse float[4] invalid"); \
	AreEqual(static_cast<int>	(expected), cfl<sse_int>::name(),  L"sse int[4] invalid"); \
	AreEqual(static_cast<float>	(expected), cfl<avx_real>::name(),	L"avx float[8] invalid"); \
	AreEqual(static_cast<int>	(expected), cfl<avx_int>::name(),	L"avx int[8] invalid")


	TEST_CLASS(TestFastLoadCostants)
	{
	public:

		TEST_METHOD(Test_Fastload_0)
		{
			VALIDATE_FASTLOAD_VALUE(_0, 0);
		}

		TEST_METHOD(Test_Fastload_1)
		{
			VALIDATE_FASTLOAD_VALUE(_1, 1);
		}

		TEST_METHOD(Test_Fastload_2)
		{
			VALIDATE_FASTLOAD_VALUE(_2, 2);
		}

		TEST_METHOD(Test_Fastload_3)
		{
			VALIDATE_FASTLOAD_VALUE(_3, 3);
		}

		TEST_METHOD(Test_Fastload_4)
		{
			VALIDATE_FASTLOAD_VALUE(_4, 4);
		}

		TEST_METHOD(Test_Fastload_5)
		{
			VALIDATE_FASTLOAD_VALUE(_5, 5);
		}

		TEST_METHOD(Test_Fastload_6)
		{
			VALIDATE_FASTLOAD_VALUE(_6, 6);
		}

		TEST_METHOD(Test_Fastload_7)
		{
			VALIDATE_FASTLOAD_VALUE(_7, 7);
		}

		TEST_METHOD(Test_Fastload_8)
		{
			VALIDATE_FASTLOAD_VALUE(_8, 8);
		}

		TEST_METHOD(Test_Fastload_9)
		{
			VALIDATE_FASTLOAD_VALUE(_9, 9);
		}

		TEST_METHOD(Test_Fastload_10)
		{
			VALIDATE_FASTLOAD_VALUE(_10, 10);
		}

		TEST_METHOD(Test_Fastload_11)
		{
			VALIDATE_FASTLOAD_VALUE(_11, 11);
		}

		TEST_METHOD(Test_Fastload_12)
		{
			VALIDATE_FASTLOAD_VALUE(_12, 12);
		}

		TEST_METHOD(Test_Fastload_13)
		{
			VALIDATE_FASTLOAD_VALUE(_13, 13);
		}

		TEST_METHOD(Test_Fastload_14)
		{
			VALIDATE_FASTLOAD_VALUE(_14, 14);
		}

		TEST_METHOD(Test_Fastload_15)
		{
			VALIDATE_FASTLOAD_VALUE(_15, 15);
		}
	};
}}}