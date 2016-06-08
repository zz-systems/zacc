//
// Created by szuyev on 17.05.16.
//

#if defined(COMPILE_SSE2) || defined(COMPILE_SSE3) || defined(COMPILE_SSSE3) || defined(COMPILE_SSE4) || defined(COMPILE_SSE4FMA)

//#if defined(COMPILE_AVX2)
//#define TYPE_PREFIX "int8"
//#elif defined(COMPILE_AVX1)
//#define TYPE_PREFIX "int4x2"
//#elif defined(COMPILE_SSE4FMA) || defined(COMPILE_SSE4) || defined(COMPILE_SSSE3) || defined(COMPILE_SSE3) || defined(COMPILE_SSE2)
//#define TYPE_PREFIX "int4"
//#else
//#define TYPE_PREFIX "int"
//#endif


#include "../gorynych/unit_test_ext.h"
#include "../../Catch/single_include/catch.hpp"
#include "../gorynych/gorynych.h"

namespace zzsystems
{
    namespace gorynych
    {
        namespace  test
        {

#if defined(COMPILE_AVX2)
    using vtest = int8<capability_AVX2>;
    #define TYPE_PREFIX "int8 - avx2"
#elif defined(COMPILE_AVX1)
    using vtest = int4x2<capability_AVX1>;
    #define TYPE_PREFIX "int4x2 - avx1"
#elif defined(COMPILE_SSE4FMA)
    using vtest = int4<capability_SSE4FMA>;
    #define TYPE_PREFIX "int4 - sse4 fma"
#elif defined(COMPILE_SSE4)
    using vtest = int4<capability_SSE4>;
#define TYPE_PREFIX "int4 - sse4"
#elif defined(COMPILE_SSSE3)
    using vtest = int4<capability_SSSE3>;
    #define TYPE_PREFIX "int4 - ssse3"
#elif defined(COMPILE_SSE3)
    using vtest = int4<capability_SSE3>;
    #define TYPE_PREFIX "int4 - sse3"
#elif defined(COMPILE_SSE2)
    using vtest = int4<capability_SSE2>;
    #define TYPE_PREFIX "int4 - sse2"
#else
    using vtest = int;
    #define TYPE_PREFIX "float1 - x87"
#endif

            using stest = int;

            //SCENARIO()
            TEST_CASE(TYPE_PREFIX" arithmetic add", "[arithmetic]")
            {
                test<vtest, stest>(45, 23, std::plus<stest>(), std::plus<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic sub", "[arithmetic]")
            {
                test<vtest, stest>(45, 23, std::minus<stest>(), std::minus<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic mul", "[arithmetic]")
            {
                test<vtest, stest>(45, 23, std::multiplies<stest>(), std::multiplies<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic div", "[aritmetic]")
            {
                test<vtest, stest>(45, 23, std::divides<stest>(), std::divides<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic neg", "[arithmetic]")
            {
                test<vtest, stest>(23, std::negate<stest>(), std::negate<vtest>());
            }

            // Bitwise =================================================================================================

            TEST_CASE(TYPE_PREFIX" bitwise and", "[bitwise]")
            {
                test<vtest, stest>(45, 23, std::bit_and<stest>(), std::bit_and<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" bitwise or", "[bitwise]")
            {
                test<vtest, stest>(45, 23, std::bit_or<stest>(), std::bit_or<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" bitwise not", "[bitwise]")
            {
                test<vtest, stest>(23, std::bit_not<stest>(), std::bit_not<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" bitwise xor", "[bitwise]")
            {
                test<vtest, stest>(45, 23, std::bit_xor<stest>(), std::bit_xor<vtest>());
            }

            TEST_CASE(TYPE_PREFIX" bitwise shift right", "[bitwise]")
            {
                for(int sa = 0; sa < 32; sa++)
                {
                    int expected = 0xFFFF'FFFF >> sa;
                    vtest calc = vtest(0xFFFF'FFFF) >> sa;
                    int tested[dim<vtest>()];
                    extract(calc, tested);

                    for(int d = 0; d < dim<vtest>(); d++)
                    {
                        CHECK(expected == tested[d]);
                    }
                }
            }

            TEST_CASE(TYPE_PREFIX" bitwise shift left", "[bitwise]")
            {
                for(int sa = 0; sa < 32; sa++)
                {
                    int expected = 1 << sa;
                    vtest calc = vtest(1) << sa;
                    int tested[dim<vtest>()];
                    extract(calc, tested);

                    for(int d = 0; d < dim<vtest>(); d++)
                    {
                        CHECK(expected == tested[d]);
                    }
                }
            }

            // Logic ===================================================================================================

            TEST_CASE(TYPE_PREFIX" logic gt", "[logic]")
            {
                btest<vtest, stest>(45, 23, std::greater<stest>(), [](auto a, auto b) { return a > b; });
                btest<vtest, stest>(23, 45, std::greater<stest>(), [](auto a, auto b) { return a > b; });
            }

            TEST_CASE(TYPE_PREFIX" logic lt", "[logic]")
            {
                btest<vtest, stest>(45, 23, std::less<stest>(), [](auto a, auto b) { return a < b; });
                btest<vtest, stest>(23, 45, std::less<stest>(), [](auto a, auto b) { return a < b; });
            }

            TEST_CASE(TYPE_PREFIX" logic eq", "[logic]")
            {
                btest<vtest, stest>(45, 23, std::equal_to<stest>(), [](auto a, auto b) { return a == b; });
                btest<vtest, stest>(23, 23, std::equal_to<stest>(), [](auto a, auto b) { return a == b; });
            }

            TEST_CASE(TYPE_PREFIX" logic neq", "[logic]")
            {
                btest<vtest, stest>(45, 23, std::not_equal_to<stest>(), [](auto a, auto b) { return a != b; });
                btest<vtest, stest>(23, 23, std::not_equal_to<stest>(), [](auto a, auto b) { return a != b; });
            }

            // Functions ===============================================================================================

            TEST_CASE(TYPE_PREFIX" functions vabs", "[functions]")
            {
                test<vtest, stest>(-45, [](auto a) { return vabs(a); }, [](auto a) { return vabs(a); });
                test<vtest, stest>(45, [](auto a) { return vabs(a); }, [](auto a) { return vabs(a); });
            }

            TEST_CASE(TYPE_PREFIX" functions vmin", "[functions]")
            {
                test<vtest, stest>(45, 23, [](auto a, auto b) { return vmin(a, b); }, [](auto a, auto b) { return vmin(a, b); });
                test<vtest, stest>(23, 45, [](auto a, auto b) { return vmin(a, b); }, [](auto a, auto b) { return vmin(a, b); });
            }

            TEST_CASE(TYPE_PREFIX" functions vmax", "[functions]")
            {
                test<vtest, stest>(45, 23, [](auto a, auto b) { return vmax(a, b); }, [](auto a, auto b) { return vmax(a, b); });
                test<vtest, stest>(23, 45, [](auto a, auto b) { return vmax(a, b); }, [](auto a, auto b) { return vmax(a, b); });
            }

            TEST_CASE(TYPE_PREFIX" functions vsel", "[functions]")
            {
                test<vtest, stest>(45, 23, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
                test<vtest, stest>(23, 45, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
                test<vtest, stest>(23, 23, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
            }
        }
    }
}
#endif