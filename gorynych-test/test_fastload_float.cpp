//
// Created by szuyev on 17.05.16.
//

#include "../gorynych/unit_test_ext.h"
#include "../../Catch/single_include/catch.hpp"
#include "../gorynych/gorynych.h"

namespace zzsystems
{
    namespace gorynych
    {
        namespace  test
        {

//#if defined(COMPILE_AVX2) || defined(COMPILE_AVX1)
//    #define TYPE_PREFIX "float8"
//#elif defined(COMPILE_SSE4FMA) || defined(COMPILE_SSE4) || defined(COMPILE_SSSE3) || defined(COMPILE_SSE3) || defined(COMPILE_SSE2)
//    #define TYPE_PREFIX "float4"
//#else
//    #define TYPE_PREFIX "float"
//#endif

#if defined(COMPILE_AVX2)
            using vreal = float8<capability_AVX2>;
    #define TYPE_PREFIX "float8 - avx2"
#elif defined(COMPILE_AVX1)
            using vreal = float8<capability_AVX1>;
    #define TYPE_PREFIX "float8 - avx1"
#elif defined(COMPILE_SSE4FMA)
            using vreal = float4<capability_SSE4FMA>;
    #define TYPE_PREFIX "float4 - sse4 fma"
#elif defined(COMPILE_SSE4)
            using vreal = float4<capability_SSE4>;
    #define TYPE_PREFIX "float4 - sse4"
#elif defined(COMPILE_SSSE3)
            using vreal = float4<capability_SSSE3>;
    #define TYPE_PREFIX "float4 - ssse3"
#elif defined(COMPILE_SSE3)
            using vreal = float4<capability_SSE3>;
    #define TYPE_PREFIX "float4 - sse3"
#elif defined(COMPILE_SSE2)
            using vreal = float4<capability_SSE2>;
    #define TYPE_PREFIX "float4 - sse2"
#else
            using vreal = float;
#define TYPE_PREFIX "float1 - x87"
#endif

            using sreal = float;
            using stesti = int;

            const float _num1 = 45.56345f;
            const float _num2 = -23.00005f;
            const float _num3 = 192.060194f;

//            TEST_CASE(TYPE_PREFIX" fastload min", "[fastload]")
//            {
//                test<vreal, sreal>([]() { return -0x7FFFFFFF; }, []() { return ccl<vreal>::min(); });
//                test<vreal, sreal>([]() { return ccl<sreal>::min(); }, []() { return ccl<vreal>::min(); });
//            }
//
//            TEST_CASE(TYPE_PREFIX" fastload max", "[fastload]")
//            {
//                test<vreal, sreal>([]() { return -0x80000000; }, []() { return ccl<vreal>::max(); });
//                test<vreal, sreal>([]() { return ccl<sreal>::max(); }, []() { return ccl<vreal>::max(); });
//            }

//            TEST_CASE(TYPE_PREFIX" fastload sign1all0", "[fastload]")
//            {
//                test<vreal, sreal>([]() { return ccl<sreal>::sign1all0(); }, []() { return ccl<vreal>::sign1all0(); });
//            }
//
//            TEST_CASE(TYPE_PREFIX" fastload sign0all1", "[fastload]")
//            {
//                test<vreal, sreal>([]() { return ccl<sreal>::sign0all1(); }, []() { return ccl<vreal>::sign0all1(); });
//            }

            
            TEST_CASE(TYPE_PREFIX" fastload 0", "[fastload]")
            {
                test<vreal, sreal>([]() { return 0; }, []() { return cfl<vreal, 0>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 1", "[fastload]")
            {
                test<vreal, sreal>([]() { return 1; }, []() { return cfl<vreal, 1>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 2", "[fastload]")
            {
                test<vreal, sreal>([]() { return 2; }, []() { return cfl<vreal, 2>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 3", "[fastload]")
            {
                test<vreal, sreal>([]() { return 3; }, []() { return cfl<vreal, 3>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 4", "[fastload]")
            {
                test<vreal, sreal>([]() { return 4; }, []() { return cfl<vreal, 4>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 5", "[fastload]")
            {
                test<vreal, sreal>([]() { return 5; }, []() { return cfl<vreal, 5>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 6", "[fastload]")
            {
                test<vreal, sreal>([]() { return 6; }, []() { return cfl<vreal, 6>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 7", "[fastload]")
            {
                test<vreal, sreal>([]() { return 7; }, []() { return cfl<vreal, 7>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 8", "[fastload]")
            {
                test<vreal, sreal>([]() { return 8; }, []() { return cfl<vreal, 8>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 9", "[fastload]")
            {
                test<vreal, sreal>([]() { return 9; }, []() { return cfl<vreal, 9>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 10", "[fastload]")
            {
                test<vreal, sreal>([]() { return 10; }, []() { return cfl<vreal, 10>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 11", "[fastload]")
            {
                test<vreal, sreal>([]() { return 11; }, []() { return cfl<vreal, 11>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 12", "[fastload]")
            {
                test<vreal, sreal>([]() { return 12; }, []() { return cfl<vreal, 12>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 13", "[fastload]")
            {
                test<vreal, sreal>([]() { return 13; }, []() { return cfl<vreal, 13>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 14", "[fastload]")
            {
                test<vreal, sreal>([]() { return 14; }, []() { return cfl<vreal, 14>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 15", "[fastload]")
            {
                test<vreal, sreal>([]() { return 15; }, []() { return cfl<vreal, 15>::val(); });
            }


        }
    }
}