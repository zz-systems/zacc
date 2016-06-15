//
// Created by szuyev on 13.06.16.
//

#include "../gorynych/gorynych.h"
#include "test_extensions.h"


namespace zzsystems { namespace gorynych { namespace test {

#define TYPE_PREFIX TEST_PREFIX("matrix")

    TEST_CASE(TYPE_PREFIX" load", "[vector]")
    {
        vec3<sint> v({2, 3, 4});

        REQUIRE(v(0) == 2);
        REQUIRE(v(1) == 3);
        REQUIRE(v(2) == 4);
    }

    TEST_CASE(TYPE_PREFIX" matrix load", "[matrix]")
    {
        mat<sint, 3, 3> v
        {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };

        CHECK(v(0) == 1);
        CHECK(v(1) == 2);
        CHECK(v(2) == 3);

        CHECK(v(3) == 4);
        CHECK(v(4) == 5);
        CHECK(v(5) == 6);

        CHECK(v(6) == 7);
        CHECK(v(7) == 8);
        CHECK(v(8) == 9);
    }

    TEST_CASE(TYPE_PREFIX" sqr magnitude", "[vector]")
    {
        vec3<sint> v({2, 3, 4});

        auto sqr_magnitude = v.sqr_magnitude();

        /// 2 * 2 + 3 * 3 + 4 * 4 = 29
        REQUIRE(sqr_magnitude == 29);
    }


    TEST_CASE(TYPE_PREFIX" magnitude", "[vector]")
    {
        vec3<sint> v({2, 3, 4});

        auto sqr_magnitude = v.magnitude();

        /// (int) sqrt(29) = 5
        REQUIRE(sqr_magnitude == 5);
    }

    TEST_CASE(TYPE_PREFIX" vector add", "[vector]")
    {
        vec3<sint> v1(1, 2, 3), v2(6, 5, 4);

        vec3<sint> result = v1 + v2;

        CHECK(result(0) == 7);
        CHECK(result(1) == 7);
        CHECK(result(2) == 7);
    }


    TEST_CASE(TYPE_PREFIX" vector sub", "[vector]")
    {
        vec3<sint> v1(1, 2, 3), v2(6, 5, 4);

        vec3<sint> result = v1 - v2;

        CHECK(result(0) == -5);
        CHECK(result(1) == -3);
        CHECK(result(2) == -1);
    }

    TEST_CASE(TYPE_PREFIX" vector scale", "[vector]")
    {
        vec3<sint> v1(1, 2, 3);

        vec3<sint> result = v1 * 2;

        CHECK(result(0) == 2);
        CHECK(result(1) == 4);
        CHECK(result(2) == 6);
    }

    TEST_CASE(TYPE_PREFIX" vector reciproc scale", "[vector]")
    {
        vec3<sint> v1(1, 2, 3);

        vec3<sint> result = v1 / 2;

        CHECK(result(0) == 0);
        CHECK(result(1) == 1);
        CHECK(result(2) == 1);
    }

    TEST_CASE(TYPE_PREFIX" row-vector * col-vector", "[vector]")
    {
        mat<sint, 1, 3> m1(2, 2, 2);
        mat<sint, 3, 1> m2(2, 2, 2);

        auto result = m1 * m2;

        CHECK(result.get_rows() == 1);
        CHECK(result.get_cols() == 1);
        CHECK(result(0) == 12);

        CHECK(result == 12);
    }

    TEST_CASE(TYPE_PREFIX" col-vector * row-vector", "[vector]")
    {
        SECTION("3 elem col vector * 3 elem row vector should yield a 3x3 matrix")
        {
//            mat<sint, 3, 1> m1(2, 4, 8);
//            mat<sint, 1, 3> m2(3, 6, 9);
//
//            auto result = m1 * m2;
//
//            CHECK(result.get_rows() == 3);
//            CHECK(result.get_cols() == 3);
//
//            CHECK(result(0, 0) == 6);
//            CHECK(result(0, 1) == 12);
//            CHECK(result(0, 2) == 18);
//
//            CHECK(result(1, 0) == 12);
//            CHECK(result(1, 1) == 24);
//            CHECK(result(1, 2) == 36);
//
//            CHECK(result(2, 0) == 24);
//            CHECK(result(2, 1) == 48);
//            CHECK(result(2, 2) == 72);
        }

        SECTION("3 elem row vector * 2 elem col vector should yield a 3x2 matrix")
        {
            mat<sint, 3, 1> m1(2, 4, 8);
            mat<sint, 1, 2> m2(3, 6);

            auto result = m1 * m2;

            CHECK(result.get_rows() == 3);
            CHECK(result.get_cols() == 2);

            CHECK(result(0, 0) == 6);
            CHECK(result(0, 1) == 12);

            CHECK(result(1, 0) == 12);
            CHECK(result(1, 1) == 24);

            CHECK(result(2, 0) == 24);
            CHECK(result(2, 1) == 48);
        }
    }


    TEST_CASE(TYPE_PREFIX" matrix * matrix", "[matrix]")
    {
        SECTION("2x3 * 3x2 should yield a 2x2 matrix")
        {
            mat<sint, 2, 3> m1(
            {
               {2, 2, 2},
               {2, 2, 2}
            });
    
            mat<sint, 3, 2> m2(
            {
                {3, 3},
                {3, 3},
                {3, 3}
            });
    
            auto result = m1 * m2;
    
            CHECK(result.get_rows() == 2);
            CHECK(result.get_cols() == 2);
    
            CHECK(result(0, 0) == 18);
            CHECK(result(0, 1) == 18);
    
            CHECK(result(1, 0) == 18);
            CHECK(result(1, 1) == 18);
        }

            
        SECTION("5x4 * 4x3 should yield a 5x3 matrix")
        {
            mat<sint, 5, 4> m1(
                {
                    { 1, 2, 3, 4 },
                    { 5, 6, 7, 8 },
                    { 9, 10, 11, 12 },
                    { 13, 14, 15, 16 },
                    { 17, 18, 19, 20 }
                }
            );
            mat<sint, 4, 3> m2(
                {
                    { 10, 20, 30 },
                    { 40, 50, 60 },
                    { 70, 80, 90 },
                    { 100, 110, 120 }
                }
            );
    
            auto result = m1 * m2;
    
            CHECK(result.get_rows() == 5);
            CHECK(result.get_cols() == 3);
    
            CHECK(result(0, 0) == 700);
            CHECK(result(0, 1) == 800);
            CHECK(result(0, 2) == 900);
    
            CHECK(result(1, 0) == 1580);
            CHECK(result(1, 1) == 1840);
            CHECK(result(1, 2) == 2100);
    
            CHECK(result(2, 0) == 2460);
            CHECK(result(2, 1) == 2880);
            CHECK(result(2, 2) == 3300);
    
            CHECK(result(3, 0) == 3340);
            CHECK(result(3, 1) == 3920);
            CHECK(result(3, 2) == 4500);
    
            CHECK(result(4, 0) == 4220);
            CHECK(result(4, 1) == 4960);
            CHECK(result(4, 2) == 5700);
        }
    }


    TEST_CASE(TYPE_PREFIX" test vector implicit init and cast", "[vector]")
    {
        vec3<sint> v {0, 1, 2};

        auto result = v + vec3<sint>({ 2, 1, 0 });

        CHECK(result.get_rows() == 1);
        CHECK(result.get_cols() == 3);

        CHECK(result(0) == 2);
        CHECK(result(1) == 2);
        CHECK(result(2) == 2);
    }

    TEST_CASE(TYPE_PREFIX" dot product", "[vector]")
    {
        vec3<sint> v {0, 1, 2}, v2 {3, 4, 5};

        auto result = v.dot(v2);

        CHECK(result == 14);
    }

    TEST_CASE(TYPE_PREFIX" dot product float", "[vector]")
    {
        vec3<sreal> v {0.5f, 0.5f, 0.5f}, v2 {2.0f, 4.0f, 8.0f};

        auto result = v.dot(v2);

        CHECK(result == 7);
    }
}}}