//---------------------------------------------------------------------------------
// The MIT License (MIT)
// 
// Copyright (c) 2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

#include "gtest/gtest.h"
#include "system/dispatcher.hpp"
#include "math/linear/generic_matrix.hpp"
#include "math/linear/specialized_matrix.hpp"

#include <cmath>
#include "util/gtest_ext.hpp"

namespace zacc { namespace test {

    using namespace zacc::math;

    TEST(vector, load)
    {
        REQUIRES(ZACC_CAPABILITIES);
        vec3<zint32> v({2, 3, 4});

        VASSERT_EQ(v(0), 2);
        VASSERT_EQ(v(1), 3);
        VASSERT_EQ(v(2), 4);
    }
    
    TEST(matrix, load)
    {
        REQUIRES(ZACC_CAPABILITIES);

        mat<zint32, 3, 3> v
        {
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9 }
        };

        VASSERT_EQ(v(0), 1);
        VASSERT_EQ(v(1), 2);
        VASSERT_EQ(v(2), 3);

        VASSERT_EQ(v(3), 4);
        VASSERT_EQ(v(4), 5);
        VASSERT_EQ(v(5), 6);

        VASSERT_EQ(v(6), 7);
        VASSERT_EQ(v(7), 8);
        VASSERT_EQ(v(8), 9);
    }
    
    TEST(vector, sqr_magnitude)
    {
        REQUIRES(ZACC_CAPABILITIES);

        vec3<zint32> v({2, 3, 4});

        auto sqr_magnitude = v.sqr_magnitude();

        /// 2 * 2 + 3 * 3 + 4 * 4 = 29
        VASSERT_EQ(sqr_magnitude, 29);
    }
    
    
    TEST(vector, magnitude)
    {
        REQUIRES(ZACC_CAPABILITIES);

        vec3<zint32> v({2, 3, 4});

        //auto sqr_magnitude = v.magnitude();

        /// (int) sqrt(29) = 5
        //VASSERT_EQ(sqr_magnitude, 5);
    }
    
    TEST(vector, add)
    {
        REQUIRES(ZACC_CAPABILITIES);

        vec3<zint32> v1(1, 2, 3), v2(6, 5, 4);

        vec3<zint32> result = v1 + v2;

        VASSERT_EQ(result(0), 7);
        VASSERT_EQ(result(1), 7);
        VASSERT_EQ(result(2), 7);
    }
    
    
    TEST(vector, sub)
    {
        REQUIRES(ZACC_CAPABILITIES);

        vec3<zint32> v1({ 1, 2, 3 }), v2({ 6, 5, 4 });

        vec3<zint32> result = v1 - v2;

        VASSERT_EQ(result(0), -5);
        VASSERT_EQ(result(1), -3);
        VASSERT_EQ(result(2), -1);
    }
    
    TEST(vector, scale)
    {
        REQUIRES(ZACC_CAPABILITIES);

        vec3<zint32> v1({ 1, 2, 3 });

        vec3<zint32> result = v1 * 2;

        VASSERT_EQ(result(0), 2);
        VASSERT_EQ(result(1), 4);
        VASSERT_EQ(result(2), 6);
    }
    
    TEST(vector, reciproc_scale)
    {
        REQUIRES(ZACC_CAPABILITIES);

        vec3<zint32> v1({ 1, 2, 3 });

        vec3<zint32> result = v1 / 2;

        VASSERT_EQ(result(0), 0);
        VASSERT_EQ(result(1), 1);
        VASSERT_EQ(result(2), 1);
    }
    
    TEST(vector, row_vector_mul_col_vector)
    {
        REQUIRES(ZACC_CAPABILITIES);

        mat<zint32, 1, 3> m1(2, 2, 2);
        mat<zint32, 3, 1> m2(2, 2, 2);

        auto result = m1 * m2;

        VASSERT_EQ(result.get_rows(), 1);
        VASSERT_EQ(result.get_cols(), 1);
        VASSERT_EQ(result(0), 12);

        zint32 t = result(0);
        VASSERT_EQ(t, 12);
    }
    
    TEST(vector, col_vector_mul_row_vector)
    {
        REQUIRES(ZACC_CAPABILITIES);

        //SECTION("3 elem col vector * 3 elem row vector should yield a 3x3 matrix")
        {
            mat<zint32, 3, 1> m1(2, 4, 8);
            mat<zint32, 1, 3> m2(3, 6, 9);

            auto result = m1 * m2;

            VASSERT_EQ(result.get_rows(), 3);
            VASSERT_EQ(result.get_cols(), 3);

            VASSERT_EQ(result(0, 0), 6);
            VASSERT_EQ(result(0, 1), 12);
            VASSERT_EQ(result(0, 2), 18);

            VASSERT_EQ(result(1, 0), 12);
            VASSERT_EQ(result(1, 1), 24);
            VASSERT_EQ(result(1, 2), 36);

            VASSERT_EQ(result(2, 0), 24);
            VASSERT_EQ(result(2, 1), 48);
            VASSERT_EQ(result(2, 2), 72);
        }
    
        //SECTION("3 elem row vector * 2 elem col vector should yield a 3x2 matrix")
        {
            mat<zint32, 3, 1> m1(2, 4, 8);
            mat<zint32, 1, 2> m2(3, 6);

            auto result = m1 * m2;

            VASSERT_EQ(result.get_rows(), 3);
            VASSERT_EQ(result.get_cols(), 2);

            VASSERT_EQ(result(0, 0), 6);
            VASSERT_EQ(result(0, 1), 12);

            VASSERT_EQ(result(1, 0), 12);
            VASSERT_EQ(result(1, 1), 24);

            VASSERT_EQ(result(2, 0), 24);
            VASSERT_EQ(result(2, 1), 48);
        }
    }
    
    
    TEST(matrix, matrix_2x3_mul_3x2)
    {
        REQUIRES(ZACC_CAPABILITIES);

        mat<zint32, 2, 3> m1(
        {
            {2, 2, 2},
            {2, 2, 2}
        });

        mat<zint32, 3, 2> m2(
        {
            {3, 3},
            {3, 3},
            {3, 3}
        });

        auto result = m1 * m2;

        VASSERT_EQ(result.get_rows(), 2);
        VASSERT_EQ(result.get_cols(), 2);

        VASSERT_EQ(result(0, 0), 18);
        VASSERT_EQ(result(0, 1), 18);

        VASSERT_EQ(result(1, 0), 18);
        VASSERT_EQ(result(1, 1), 18);
    }

    TEST(matrix, matrix_5x4_mul_4x3)
    {
        REQUIRES(ZACC_CAPABILITIES);

        mat<zint32, 5, 4> m1
        {
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 },
            { 9, 10, 11, 12 },
            { 13, 14, 15, 16 },
            { 17, 18, 19, 20 }
        };

        mat<zint32, 4, 3> m2
        {
            { 10, 20, 30 },
            { 40, 50, 60 },
            { 70, 80, 90 },
            { 100, 110, 120 }
        };
    
        auto result = m1 * m2;

        VASSERT_EQ(result.get_rows(), 5);
        VASSERT_EQ(result.get_cols(), 3);

        VASSERT_EQ(result(0, 0), 700);
        VASSERT_EQ(result(0, 1), 800);
        VASSERT_EQ(result(0, 2), 900);

        VASSERT_EQ(result(1, 0), 1580);
        VASSERT_EQ(result(1, 1), 1840);
        VASSERT_EQ(result(1, 2), 2100);

        VASSERT_EQ(result(2, 0), 2460);
        VASSERT_EQ(result(2, 1), 2880);
        VASSERT_EQ(result(2, 2), 3300);

        VASSERT_EQ(result(3, 0), 3340);
        VASSERT_EQ(result(3, 1), 3920);
        VASSERT_EQ(result(3, 2), 4500);

        VASSERT_EQ(result(4, 0), 4220);
        VASSERT_EQ(result(4, 1), 4960);
        VASSERT_EQ(result(4, 2), 5700);
    }

    
    
    TEST(vector, vector_implicit_init_and_cast)
    {
        REQUIRES(ZACC_CAPABILITIES);

        vec3<zint32> v {0, 1, 2};

        auto result = v + vec3<zint32>({ 2, 1, 0 });

        VASSERT_EQ(result.get_rows(), 3);
        VASSERT_EQ(result.get_cols(), 1);

        VASSERT_EQ(result(0), 2);
        VASSERT_EQ(result(1), 2);
        VASSERT_EQ(result(2), 2);
    }
    
    TEST(vector, dot_product)
    {
        REQUIRES(ZACC_CAPABILITIES);

        vec3<zint32> v {0, 1, 2}, v2 {3, 4, 5};

        auto result = v.dot(v2);

        VASSERT_EQ(result, 14);
    }
    
    TEST(vector, dot_product_float)
    {
        REQUIRES(ZACC_CAPABILITIES);

        vec3<zfloat32> v {0.5f, 0.5f, 0.5f}, v2 {2.0f, 4.0f, 8.0f};

        auto result = v.dot(v2);

        VASSERT_EQ(result, 7);
    }
}}