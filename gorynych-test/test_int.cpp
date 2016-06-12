//
// Created by szuyev on 17.05.16.
//

//#include "../Catch/single_include/catch.hpp"
#include "../gorynych/gorynych.h"

#include "test_extensions.h"

namespace zzsystems { namespace gorynych { namespace  test {

#define TYPE_PREFIX TEST_PREFIX("int")

            //SCENARIO()
            TEST_CASE(TYPE_PREFIX" arithmetic add", "[arithmetic]")
            {
                test<vint, sint>(45, 23, std::plus<sint>(), std::plus<vint>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic sub", "[arithmetic]")
            {
                test<vint, sint>(45, 23, std::minus<sint>(), std::minus<vint>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic mul", "[arithmetic]")
            {
                test<vint, sint>(45, 23, std::multiplies<sint>(), std::multiplies<vint>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic div", "[aritmetic]")
            {
                test<vint, sint>(45, 23, std::divides<sint>(), std::divides<vint>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic neg", "[arithmetic]")
            {
                test<vint, sint>(23, std::negate<sint>(), std::negate<vint>());
            }

            // Bitwise =================================================================================================

            TEST_CASE(TYPE_PREFIX" bitwise and", "[bitwise]")
            {
                test<vint, sint>(45, 23, std::bit_and<sint>(), std::bit_and<vint>());
            }

            TEST_CASE(TYPE_PREFIX" bitwise or", "[bitwise]")
            {
                test<vint, sint>(45, 23, std::bit_or<sint>(), std::bit_or<vint>());
            }

            TEST_CASE(TYPE_PREFIX" bitwise not", "[bitwise]")
            {
                test<vint, sint>(23, std::bit_not<sint>(), std::bit_not<vint>());
            }

            TEST_CASE(TYPE_PREFIX" bitwise xor", "[bitwise]")
            {
                test<vint, sint>(45, 23, std::bit_xor<sint>(), std::bit_xor<vint>());
            }

            TEST_CASE(TYPE_PREFIX" bitwise shift right", "[bitwise]")
            {
                for(int sa = 0; sa < 32; sa++)
                {
                    int expected = 0xFFFF'FFFF >> sa;
                    vint calc = vint(0xFFFF'FFFF) >> sa;
                    SIMD_ALIGN int tested[dim<vint>()];
                    extract(calc, tested);

                    for(int d = 0; d < dim<vint>(); d++)
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
                    vint calc = vint(1) << sa;
					SIMD_ALIGN int tested[dim<vint>()];
                    extract(calc, tested);

                    for(int d = 0; d < dim<vint>(); d++)
                    {
                        CHECK(expected == tested[d]);
                    }
                }
            }

            // Logic ===================================================================================================

            TEST_CASE(TYPE_PREFIX" logic gt", "[logic]")
            {
                btest<vint, sint>(45, 23, std::greater<sint>(), [](auto a, auto b) { return a > b; });
                btest<vint, sint>(23, 45, std::greater<sint>(), [](auto a, auto b) { return a > b; });
            }

            TEST_CASE(TYPE_PREFIX" logic lt", "[logic]")
            {
                btest<vint, sint>(45, 23, std::less<sint>(), [](auto a, auto b) { return a < b; });
                btest<vint, sint>(23, 45, std::less<sint>(), [](auto a, auto b) { return a < b; });
            }

            TEST_CASE(TYPE_PREFIX" logic eq", "[logic]")
            {
                btest<vint, sint>(45, 23, std::equal_to<sint>(), [](auto a, auto b) { return a == b; });
                btest<vint, sint>(23, 23, std::equal_to<sint>(), [](auto a, auto b) { return a == b; });
            }

            TEST_CASE(TYPE_PREFIX" logic neq", "[logic]")
            {
                btest<vint, sint>(45, 23, std::not_equal_to<sint>(), [](auto a, auto b) { return a != b; });
                btest<vint, sint>(23, 23, std::not_equal_to<sint>(), [](auto a, auto b) { return a != b; });
            }

            // Functions ===============================================================================================

            TEST_CASE(TYPE_PREFIX" functions vabs", "[functions]")
            {
                test<vint, sint>(-45, [](auto a) { return vabs(a); }, [](auto a) { return vabs(a); });
                test<vint, sint>(45, [](auto a) { return vabs(a); }, [](auto a) { return vabs(a); });
            }

            TEST_CASE(TYPE_PREFIX" functions vmin", "[functions]")
            {
                test<vint, sint>(45, 23, [](auto a, auto b) { return vmin(a, b); }, [](auto a, auto b) { return vmin(a, b); });
                test<vint, sint>(23, 45, [](auto a, auto b) { return vmin(a, b); }, [](auto a, auto b) { return vmin(a, b); });
            }

            TEST_CASE(TYPE_PREFIX" functions vmax", "[functions]")
            {
                test<vint, sint>(45, 23, [](auto a, auto b) { return vmax(a, b); }, [](auto a, auto b) { return vmax(a, b); });
                test<vint, sint>(23, 45, [](auto a, auto b) { return vmax(a, b); }, [](auto a, auto b) { return vmax(a, b); });
            }

            TEST_CASE(TYPE_PREFIX" functions vsel", "[functions]")
            {
                test<vint, sint>(45, 23, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
                test<vint, sint>(23, 45, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
                test<vint, sint>(23, 23, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
            }
        }
    }
}