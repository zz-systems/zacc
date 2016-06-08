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
    using vtest = float8<capability_AVX2>;
    #define TYPE_PREFIX "float8 - avx2" 
#elif defined(COMPILE_AVX1)
    using vtest = float8<capability_AVX1>;
    #define TYPE_PREFIX "float8 - avx1"
#elif defined(COMPILE_SSE4FMA)
    using vtest = float4<capability_SSE4FMA>;
    #define TYPE_PREFIX "float4 - sse4 fma"
#elif defined(COMPILE_SSE4)
    using vtest = float4<capability_SSE4>;
    #define TYPE_PREFIX "float4 - sse4"
#elif defined(COMPILE_SSSE3)
    using vtest = float4<capability_SSSE3>;
    #define TYPE_PREFIX "float4 - ssse3"
#elif defined(COMPILE_SSE3)
    using vtest = float4<capability_SSE3>;
    #define TYPE_PREFIX "float4 - sse3"
#elif defined(COMPILE_SSE2)
    using vtest = float4<capability_SSE2>;
    #define TYPE_PREFIX "float4 - sse2"
#else
    using vtest = float;
    #define TYPE_PREFIX "float1 - x87"
#endif

using stest = float;
using stesti = int;

            const float _num1 = 45.56345f;
            const float _num2 = -23.00005f;
            const float _num3 = 192.060194f;

            //SCENARIO()
            TEST_CASE(TYPE_PREFIX" arithmetic add", "[arithmetic]")
            {
                test<vtest, stest>(_num1, _num2, std::plus<stest>(), std::plus<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic sub", "[arithmetic]")
            {
                test<vtest, stest>(_num1, _num2, std::minus<stest>(), std::minus<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic mul", "[arithmetic]")
            {
                test<vtest, stest>(_num1, _num2, std::multiplies<stest>(), std::multiplies<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic div", "[aritmetic]")
            {
                test<vtest, stest>(_num1, _num2, std::divides<stest>(), std::divides<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic neg", "[arithmetic]")
            {
                test<vtest, stest>(_num2, std::negate<stest>(), std::negate<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" fused multiply add", "[arithmetic]")
            {
                test<vtest, stest>(_num1, _num2, _num3, [](auto a, auto b, auto c) { return a * b + c; }, [](auto a, auto b, auto c) { return vfmadd(a, b, c); });
            }

            TEST_CASE(TYPE_PREFIX" fused multiply sub", "[arithmetic]")
            {
                test<vtest, stest>(_num1, _num2, _num3, [](auto a, auto b, auto c) { return a * b - c; }, [](auto a, auto b, auto c) { return vfmsub(a, b, c); });
            }

            // Bitwise =================================================================================================

//            TEST_CASE(TYPE_PREFIX" bitwise and", "[bitwise]")
//            {
//                test<vtest, stest>(_num1, _num2, std::bit_and<stest>(), std::bit_and<vtest>());
//            }
//
//            TEST_CASE(TYPE_PREFIX" bitwise or", "[bitwise]")
//            {
//                test<vtest, stest>(_num1, _num2, std::bit_or<stest>(), std::bit_or<vtest>());
//            }
//
//            TEST_CASE(TYPE_PREFIX" bitwise not", "[bitwise]")
//            {
//                test<vtest, stest>(_num2, std::bit_not<stest>(), std::bit_not<vtest>());
//            }
//
//            TEST_CASE(TYPE_PREFIX" bitwise xor", "[bitwise]")
//            {
//                test<vtest, stest>(_num1, _num2, std::bit_xor<stest>(), std::bit_xor<vtest>());
//            }

            // Logic ===================================================================================================

            TEST_CASE(TYPE_PREFIX" logic gt", "[logic]")
            {
                btest<vtest, stest>(_num1, _num2, std::greater<stest>(), [](auto a, auto b) { return a > b; });
                btest<vtest, stest>(_num2, _num1, std::greater<stest>(), [](auto a, auto b) { return a > b; });
            }

            TEST_CASE(TYPE_PREFIX" logic lt", "[logic]")
            {
                btest<vtest, stest>(_num1, _num2, std::less<stest>(), [](auto a, auto b) { return a < b; });
                btest<vtest, stest>(_num2, _num1, std::less<stest>(), [](auto a, auto b) { return a < b; });
            }

            TEST_CASE(TYPE_PREFIX" logic eq", "[logic]")
            {
                btest<vtest, stest>(_num1, _num2, std::equal_to<stest>(), [](auto a, auto b) { return a == b; });
                btest<vtest, stest>(_num2, _num2, std::equal_to<stest>(), [](auto a, auto b) { return a == b; });
            }

            TEST_CASE(TYPE_PREFIX" logic neq", "[logic]")
            {
                btest<vtest, stest>(_num1, _num2, std::not_equal_to<stest>(), [](auto a, auto b) { return a != b; });
                btest<vtest, stest>(_num2, _num2, std::not_equal_to<stest>(), [](auto a, auto b) { return a != b; });
            }

            // Functions ===============================================================================================

            TEST_CASE(TYPE_PREFIX" functions vabs", "[functions]")
            {
                test<vtest, stest>(_num1, [](auto a) { return vabs(a); }, [](auto a) { return vabs(a); });
                test<vtest, stest>(_num2, [](auto a) { return vabs(a); }, [](auto a) { return vabs(a); });
            }

            TEST_CASE(TYPE_PREFIX" functions vmin", "[functions]")
            {
                test<vtest, stest>(_num1, _num2, [](auto a, auto b) { return vmin(a, b); }, [](auto a, auto b) { return vmin(a, b); });
                test<vtest, stest>(_num2, _num1, [](auto a, auto b) { return vmin(a, b); }, [](auto a, auto b) { return vmin(a, b); });
            }

            TEST_CASE(TYPE_PREFIX" functions vmax", "[functions]")
            {
                test<vtest, stest>(_num1, _num2, [](auto a, auto b) { return vmax(a, b); }, [](auto a, auto b) { return vmax(a, b); });
                test<vtest, stest>(_num2, _num1, [](auto a, auto b) { return vmax(a, b); }, [](auto a, auto b) { return vmax(a, b); });
            }

            TEST_CASE(TYPE_PREFIX" functions vsel", "[functions]")
            {
                test<vtest, stest>(_num1, _num2, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
                test<vtest, stest>(_num2, _num1, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
                test<vtest, stest>(_num2, _num2, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
            }
            
            // Rounding ================================================================================================

            TEST_CASE(TYPE_PREFIX" truncate", "[rounding]")
            {
                test<vtest, stest>(_num1, [](auto a) { return std::trunc(a); }, [](auto a) { return vtrunc(a); });
                test<vtest, stest>(_num2, [](auto a) { return std::trunc(a); }, [](auto a) { return vtrunc(a); });
                test<vtest, stest>(_num3, [](auto a) { return std::trunc(a); }, [](auto a) { return vtrunc(a); });
            }

            TEST_CASE(TYPE_PREFIX" floor", "[rounding]")
            {
                test<vtest, stest>(_num1, [](auto a) { return std::floor(a); }, [](auto a) { return vfloor(a); });
                test<vtest, stest>(_num2, [](auto a) { return std::floor(a); }, [](auto a) { return vfloor(a); });
                test<vtest, stest>(_num3, [](auto a) { return std::floor(a); }, [](auto a) { return vfloor(a); });
            }

            TEST_CASE(TYPE_PREFIX" ceil", "[rounding]")
            {
                test<vtest, stest>(_num1, [](auto a) { return std::ceil(a); }, [](auto a) { return vceil(a); });
                test<vtest, stest>(_num2, [](auto a) { return std::ceil(a); }, [](auto a) { return vceil(a); });
                test<vtest, stest>(_num3, [](auto a) { return std::ceil(a); }, [](auto a) { return vceil(a); });
            }

            TEST_CASE(TYPE_PREFIX" round", "[rounding]")
            {
                test<vtest, stest>(_num1, [](auto a) { return std::round(a); }, [](auto a) { return vround(a); });
                test<vtest, stest>(_num2, [](auto a) { return std::round(a); }, [](auto a) { return vround(a); });
                test<vtest, stest>(_num3, [](auto a) { return std::round(a); }, [](auto a) { return vround(a); });
            }
        }
    }
}